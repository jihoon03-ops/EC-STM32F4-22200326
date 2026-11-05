
#include "ecGPIO2.h"
#include "ecSysTick2.h"
#include "ecRCC2.h"
#include "ecTIM2.h"
#include "ecPWM2.h"
#include "ecEXTI2.h"

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
    {{S1, S0}, {0.0f,   LOW}},
    {{S2, S1}, {0.5f,  HIGH}},
    {{S0, S2}, {0.8f, HIGH}}
};

volatile uint8_t state = 0;
volatile uint8_t flag_button = 0;
volatile uint8_t flag_blink = 0;
uint8_t count = 0;

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

    // TIM_UI_init(TIM3, 500);           // UEV every 500 msec

    EXTI_init(BUTTON_PIN, FALL, 10);

    PWM_init(PWM_PIN, 1);
    TIM_UI_init(TIM3, 500);
}


int main(void){
    setup();
    GPIO_write(DIR_PIN, HIGH);
    uint8_t IR_PROXIMITY_state = 0;

    while(1){
        PWM_duty(PWM_PIN ,mode[state].out[0]);
        GPIO_write(LED_PIN, mode[state].out[1]);
        IR_PROXIMITY_state = GPIO_read(IR_PROXIMITY_SENSOR_PIN);

        if (IR_PROXIMITY_state == 1){
            PWM_duty(PWM_PIN, 0.0f);
            blink();
        }
        else {
            if (flag_button == 1){
                next_state();
                flag_button = 0;
            }
        }
    }
}



void blink(void){
    // count = 0;
    // while(count< 5){
    //     if (flag_blink ==1)
    //     GPIO_write(LED_PIN, HIGH);
    //     else if (flag_blink ==0)
    //     GPIO_write(LED_PIN,LOW);
    //     delay_ms(500);
    //     count+=1;
    GPIO_write(LED_PIN, HIGH);
    delay_ms(500);
    GPIO_write(LED_PIN,LOW);
    delay_ms(500);
     GPIO_write(LED_PIN, HIGH);
    delay_ms(500);
    GPIO_write(LED_PIN,LOW);
    delay_ms(500);
}

// void TIM3_IRQHandler(void){
//     if(is_UIF(TIM3)){           // Check UIF(update interrupt flag)
//         flag_blink = 1;
//         clear_UIF(TIM3);        // Clear TIM_UI flag
//     }
// }

void next_state(void){
    state = mode[state].next[0];
}

void EXTI15_10_IRQHandler(void){
    if (is_pending_EXTI(BUTTON_PIN)){
        flag_button = 1;
        clear_pending_EXTI(BUTTON_PIN);
    }
}

