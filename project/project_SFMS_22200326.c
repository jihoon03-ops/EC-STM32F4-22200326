#include "ecSTM32F4v2.h"

#define VENT_FAN        PA_15
#define WINDOW_SERVO    PC_7
#define LED PB_7
#define LIGHT_SENSOR    PA_0
#define MOISTURE_SENSOR PA_1
#define DHT11           PA_6
#define LCD_SCL         PB_8
#define LCD_SDA         PB_9
#define BT_TX           PA_11
#define BT_RX           PA_12
#define DEBUG_TX        PA_2
#define DEBUG_RX        PA_3
// #define SPARE           PB_6
#define MANUAL          0
#define AUTO            1

#define NORMAL          0
#define DRY             1

#define LIGHT_DARK      3000
#define LIGHT_BRIGHT    1500
#define LIGHT_HYST      100

#define MOIST_DRY       1500
#define MOIST_WET       2000

#define TEMP_HIGH       28
#define TEMP_LOW        26

#define HUMI_HIGH       70
#define HUMI_LOW        60

volatile uint32_t light_val = 0;
volatile uint32_t moisture_val = 0;
volatile uint32_t temp_val = 0;
volatile uint32_t humi_val = 0;
// volatile uint32_t dht_err_cnt = 0;
// volatile uint32_t dht_fault = 0;
volatile uint32_t mode = MANUAL;
// volatile uint32_t alarm_state = NORMAL;
volatile uint32_t alarm_ack = 0;
volatile uint32_t LED_duty = 0;
// volatile uint32_t vent = 0;

// volatile uint32_t flag_500ms = 0;
// volatile uint32_t flag_dht11 = 0;
// volatile uint32_t dht_tick_cnt = 0;
// volatile uint32_t dry_cnt = 0;
// volatile uint32_t wet_cnt = 0;
// volatile uint32_t auto_delay_cnt = 0;
// volatile uint32_t blink_toggle = 0;
volatile uint32_t fan_on = 0;
volatile uint32_t window_open = 0;
volatile uint32_t flag_bt_msg = 0;

//variable for LCD
int      err   = 0;
char     lcd_line[20];

void setup(void){
    RCC_PLL_init();
    SysTick_init();

    USART_init(USART2, DEBUG_TX, DEBUG_RX, 9600);
    // [디버깅] setup() 도중 멈출 경우 UART2 문제인지 이후 초기화(LCD/TIM1) 문제인지 분리하기 위한 체크포인트
    printf("UART2 OK\r\n");
    USART_init(USART6, BT_TX, BT_RX, 9600);

    PWM_init(VENT_FAN, 1);
    PWM_duty(VENT_FAN, 0.0);

    PWM_init(WINDOW_SERVO, 20);
    PWM_pulsewidth_us(WINDOW_SERVO, 500);

    DHT11_init(DHT11);
    I2C1_init();
    LCD_init();

    PWM_init(LED, 1);
    PWM_duty(LED, 0.0);

    TIM_UI_init(TIM1, 500);

    JADC_init(LIGHT_SENSOR);
    JADC_init(MOISTURE_SENSOR);

    PinName_t seqCHn[2] = {LIGHT_SENSOR, MOISTURE_SENSOR};
    JADC_sequence(seqCHn, 2);
    JADC_trigger_init(TIM5, 125, ADC_RISE);

    printf("MCU INITIALIZED \r\n");

    
}

int main(void){
    // 이전 출력 상태를 기억하는 지역 변수 (초기값을 초기 상태와 다르게 두어 부팅 직후 1회 출력 보장)
    // - 왜 매 루프마다 PWM_duty()를 부르지 않는가?
    //   타이머 파형 자체가 끊기지는 않지만(OCxPE 프리로드 활성), 매 루프 핀맵/실수 연산을 반복하는
    //   CPU 낭비를 없애기 위해 상태가 바뀐 순간에만 1회 레지스터를 갱신함.
    static uint32_t prev_fan_on = 1;
    static uint32_t prev_window_open = 1;
    static uint32_t prev_LED_duty = 101;    // 유효 범위(0~100) 밖 값으로 초기화하여 첫 루프 보장

    setup();

    // Does the LCD answer ?  A module with the wrong address stays blank.
	err = I2C1_write(LCD_ADDR, LCD_BACKLIGHT);
	if(err)	printf("LCD NOT found. Check the wiring\r\n");
	else	printf("LCD found at 0x%02X\r\n", LCD_ADDR);

    while(1){
        if (mode == AUTO){
            printf("value: %lu \r\n", light_val);

            if (LIGHT_DARK < light_val){
                LED_duty = 100;
            }
            else if (LIGHT_BRIGHT > light_val){
                LED_duty = 0;
            }
            else{
                // 선형 보간: 조도 범위(1500~3000)를 0~100% 정수로 매핑
                LED_duty = (uint32_t)((100.0f / (LIGHT_DARK - LIGHT_BRIGHT)) * (light_val - LIGHT_BRIGHT));
            }
            
            delay_ms(1000);
        }
        else if (mode == MANUAL){
            // MANUAL 모드에서는 블루투스 ISR이 갱신한 LED_duty, fan_on, window_open 값을 그대로 유지
        }

        // [공통 액추에이터 출력부] 모드 분기 바깥에 두어 AUTO/MANUAL 어느 쪽에서 값이 바뀌든 일관되게 반영
        if (prev_LED_duty != LED_duty){
            // 경계 조건: 정수 나눗셈(0)을 막기 위해 반드시 실수 리터럴 100.0f로 나눈다.
            PWM_duty(LED, LED_duty / 100.0f);
            prev_LED_duty = LED_duty;
        }
        if (prev_fan_on != fan_on){
            // 0과 1은 float로 암시적 형변환해도 손실이 없으나, 가독성과 추후 속도 조절 확장을 위해 명시적으로 지정
            PWM_duty(VENT_FAN, fan_on ? 1.0f : 0.0f);
            prev_fan_on = fan_on;
        }
        if (prev_window_open != window_open){
            // 서보모터: 닫힘(500 us) / 열림(1500 us, 필요 시 기구 각도에 맞게 1500~2500 us 범위에서 조정)
            PWM_pulsewidth_us(WINDOW_SERVO, window_open ? 1500 : 500);
            prev_window_open = window_open;
        }

        // [상태 변경 보고부] mode 분기 바깥에 배치해야 'M'으로 AUTO 전환 직후에도 메시지가 누락되지 않음
        if (flag_bt_msg){
            // 왜 출력 함수 호출 전에 플래그를 0으로 내리는가?
            // UART 전송(~15 ms 이상 소요) 도중에 다음 블루투스 입력 인터럽트가 들어왔을 때
            // 마지막에 플래그를 0으로 덮어써서 새 이벤트를 잃어버리는 경쟁 상태(Race condition)를 방지하기 위함.
            flag_bt_msg = 0;

            char bt_buf[96];
            sprintf(bt_buf, "\r\nMODE:%s | LED:%lu%% | FAN:%s | WIN:%s | ACK:%lu\r\n",
                    (mode == AUTO) ? "AUTO" : "MANUAL",
                    LED_duty,
                    (fan_on == 0) ? "OFF" : "ON",
                    (window_open == 0) ? "CLOSED" : "OPENED",
                    alarm_ack);

            // PC 디버그(USART2)와 블루투스 터미널(USART6) 양쪽으로 상태 메시지 전송
            printf("%s", bt_buf);
            USART_write(USART6, (uint8_t*)bt_buf, strlen(bt_buf));
        }

        //LCD print
        snprintf(lcd_line, sizeof(lcd_line), "(%02d\xDF, %02d%%, LED %d%%)", temp_val, humi_val, LED_duty);
	    LCD_setCursor(0, 0);
		LCD_print(lcd_line);
     
    }
}

//light & moisture
void ADC_IRQHandler(void){
    if(is_ADC_JEOC()){      // one JEOC after the whole sequence
        light_val = JADC_read(1);
        moisture_val = JADC_read(2);
        clear_ADC_JEOC();
    }
    if(is_ADC_OVR()){
        clear_ADC_OVR();
    }
}

void USART6_IRQHandler(void){
    if(is_USART_RXNE(USART6)){
        uint8_t bt_data = USART_read(USART6);

        USART_write(USART6, &bt_data, 1);  // Echo to Bluetooth Tera Term
        USART2_write(&bt_data, 1);  // Echo to USB Tera Term

        if(bt_data == 'M') {
            mode ^= 1;
            flag_bt_msg = 1;
        }
        else if(mode == MANUAL && bt_data >= '0' && bt_data <= '5'){
            LED_duty = (bt_data - '0') * 20;
            flag_bt_msg = 1;
        }
        else if(mode == MANUAL && bt_data == 'F'){
            fan_on ^= 1;
            flag_bt_msg = 1;
        }
        else if(mode == MANUAL && bt_data == 'W'){
            window_open ^= 1;
            flag_bt_msg = 1;
        }
        else if(bt_data == 'A'){
            // 알람 확인(Ack)은 AUTO/MANUAL 어느 모드에서든 가능해야 하므로 mode == MANUAL 조건 제외
            alarm_ack = 1;
            flag_bt_msg = 1;
        }
    }
}

// TIM1 업데이트 인터럽트 핸들러 (500 ms 제어 루프 기준)
// - 왜 빈 핸들러라도 반드시 정의해야 하는가?
//   ecTIM2의 TIM_init()이 PSC 설정 후 UG 이벤트를 강제 발생시키지 않기 때문에,
//   첫 주기는 리셋값 PSC=0(84 MHz)으로 동작해 약 60 us 만에 첫 UIF 인터럽트가 발생한다.
//   핸들러가 없으면 setup() 도중 Default_Handler(무한 정지)로 빠져 MCU가 멈춘다.
void TIM1_UP_TIM10_IRQHandler(void){
    // TIM1과 TIM10이 같은 IRQ 벡터를 공유하므로 반드시 TIM1의 UIF 비트를 확인한다.
    if(is_UIF(TIM1)){
        // 인터럽트 플래그를 지우지 않으면 핸들러 종료 즉시 재진입하는 무한 루프에 빠짐
        clear_UIF(TIM1);
    }
}

void USART2_IRQHandler(void){
    if(is_USART2_RXNE()){
        uint8_t pc_data = USART2_read();
        USART2_write(&pc_data, 1);  // Echo USB typing to check USB connection
    }
}