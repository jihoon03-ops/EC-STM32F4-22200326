
//pin configuration
#include "ecSTM32F4v2.h"

#define VENT_FAN        PA_15
#define WINDOW_SERVO    PC_7
#define LED             PB_7
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

//threshold value
#define LIGHT_DARK      4000
#define LIGHT_BRIGHT    100
#define LIGHT_HYST      100

#define MOIST_DRY       1500
#define MOIST_WET       2000

#define TEMP_HIGH       28
#define TEMP_LOW        26

#define HUMI_HIGH       70
#define HUMI_LOW        60


//Analog Sensor parameter//
volatile uint32_t light_sensor_val, moist_sensor_val;
PinName_t seqCHn[2] = {LIGHT_SENSOR, MOISTURE_SENSOR};
float LED_duty;
float slope = (1/(LIGHT_DARK-LIGHT_BRIGHT));
uint8_t mode = AUTO; 

void setup(void){
    RCC_PLL_init();         // System Clock = 84MHz
    USART2_init();           // UART2 Init
    SysTick_init();         // SysTick Init

    //PWM
    PWM_init(LED, 1);    //1[ms]

    // JADC Init  Default: SW trigger, no interrupt
    JADC_init(LIGHT_SENSOR);
    JADC_init(MOISTURE_SENSOR);
    // JADC channel sequence setting
    JADC_sequence(seqCHn, 2);

    // HW trigger : TIM5 TRGO @ 1msec - enables JEOC interrupt
    JADC_trigger_init(TIM5, 125, ADC_RISE);

    USART2_init();
    USART2_baud(9600);
}

int main(void){
    
    setup();

    while(1){

        if (mode == AUTO){
            printf("value: %.1f \r\n", light_sensor_val);

            if (LIGHT_DARK < light_sensor_val){
                PWM_duty(LED, 1.0f);
            }
            else if (LIGHT_BRIGHT > light_sensor_val){
                PWM_duty(LED, 0.0f);
            }
            else{
                LED_duty = slope * (light_sensor_val - LIGHT_BRIGHT); 
                PWM_duty(LED, LED_duty);
            }
            delay_ms(1000);
        }
        else if (mode ==MANUAL){

        }
        else {

        }
    }
}


void ADC_IRQHandler(void){
    if(is_ADC_JEOC()){      // one JEOC after the whole sequence
        light_sensor_val = JADC_read(1);
        moist_sensor_val = JADC_read(2);
        clear_ADC_JEOC();
    }
}