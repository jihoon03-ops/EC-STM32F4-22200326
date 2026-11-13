
#include "ecGPIO2.h"
#include "ecSysTick2.h"
#include "ecRCC2.h"
#include "ecTIM2.h"
#include "ecPWM2.h"
#include "ecEXTI2.h"
#include "ecUART2.h"

#define BUTTON_PIN              PC_13
#define DIR_PIN                 PC_2
#define PWM_PIN                 PA_0
#define LED_PIN                 PA_5
#define IR_PROXIMITY_SENSOR_PIN PA_1

typedef enum{
    S0, S1, S2
} state_num;

typedef struct{
    uint32_t next[2];
    float  out[2];
} state_t;

state_t mode[3] = {
    {{S1, S0}, {0.0f, LOW}},
    {{S2, S1}, {0.5f, HIGH}},
    {{S0, S2}, {1.0f, HIGH}}
};

volatile uint8_t state = 0;
volatile uint8_t flag_button = 0;
volatile uint8_t flag_stop = 0;
volatile uint8_t flag_timer = 0;

void blink(void);
void next_state(void);


void setup(void){
    RCC_PLL_init();
    SysTick_init();

    GPIO_init(BUTTON_PIN, INPUT);
    GPIO_pupd(BUTTON_PIN, PULLUP);
    
    GPIO_init(DIR_PIN, OUTPUT);
    GPIO_otype(DIR_PIN, PUSH_PULL);

    GPIO_init(LED_PIN, OUTPUT);
    GPIO_otype(LED_PIN, PUSH_PULL);

    GPIO_init(IR_PROXIMITY_SENSOR_PIN, INPUT);
    GPIO_pupd(IR_PROXIMITY_SENSOR_PIN, PULLUP);

    EXTI_init(BUTTON_PIN, FALL, 10);
  
    PWM_init(PWM_PIN, 1);   //Timer 2, channel 1

    // Configure USART2: USB Serial connection to PC (9600 baud)
    USART2_init();
    USART2_baud(BAUD_9600);

    TIM_UI_init(TIM3, 2000);     // UEV every 2sec
}
    


int main(void){
    setup();
    uint8_t IR_PROXIMITY_state = 0;
   

    while(1){
        PWM_duty(PWM_PIN ,mode[state].out[0]);
        GPIO_write(LED_PIN, mode[state].out[1]);
        IR_PROXIMITY_state = !(GPIO_read(IR_PROXIMITY_SENSOR_PIN));

        if (IR_PROXIMITY_state){
            EXTI_disable(BUTTON_PIN); 
            PWM_duty(PWM_PIN, 0.0f);
            blink();
            EXTI_enable(BUTTON_PIN);
        } 
        else {
            if (flag_button){
                delay_ms(200);
                next_state();
                flag_button = 0;
            }
        }
        if (flag_timer){
            if(IR_PROXIMITY_state){
                printf("MODE: %d, PWM_duty_ratio: %.1f, emergency_STOP: %d\r\n", 
                state, 0.0f, IR_PROXIMITY_state);
            }
            else{
            printf("MODE: %d, PWM_duty_ratio: %.1f, emergency_STOP: %d\r\n", 
                state, mode[state].out[0], IR_PROXIMITY_state);
            }
            flag_timer = 0;
        }
    }
}



void blink(void){
 
    GPIO_write(LED_PIN, HIGH);
    delay_ms(500);
    GPIO_write(LED_PIN,LOW);
    delay_ms(500);
    GPIO_write(LED_PIN, HIGH);
    delay_ms(500);
    GPIO_write(LED_PIN,LOW);
    delay_ms(500);
}


void next_state(void){
    state = mode[state].next[0];
}

void EXTI15_10_IRQHandler(void){
    if (is_pending_EXTI(BUTTON_PIN)){
        flag_button = 1;
        clear_pending_EXTI(BUTTON_PIN);
    }
}

void TIM3_IRQHandler(void){     // set flag every 500msec
    if(is_UIF(TIM3)){           // Check UIF(update interrupt flag)
        flag_timer = 1;               // set flag 
        clear_UIF(TIM3);        // Clear TIM_UI flag
    }
}

