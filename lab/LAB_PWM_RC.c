/*----------------------------------------------------------------@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Jihoon Park
Created          : 10-13-2026
Modified         : 11-01-2026 
Language/ver     : C in VS Code

Description      : Tutorial - PWM
                   PA_5 (TIM2_CH1, Nucleo LD2) : 100 Hz, duty sweep 0 -> 100%                   
/----------------------------------------------------------------*/

// #include "ecSTM32F411.h"
#include "ecGPIO2.h"
#include "ecSysTick2.h"
#include "ecRCC2.h"
#include "ecTIM2.h"
#include "ecPWM2.h"
#include "ecEXTI2.h"

// Button Pin & PWM Pin
#define PWM     PA_1
#define BUTTON  PC_13

volatile uint8_t flag = 0;
volatile uint8_t initialize = 0;


// Initialiization 
void setup(void) {  
    RCC_PLL_init();
    SysTick_init();

    TIM_UI_init(TIM3, 500);           // UEV every 500 msec

    GPIO_init(BUTTON, INPUT);  // INPUT for EVAL board
    GPIO_pupd(BUTTON, PULLUP);  // PULL-UP for EVAL board  

    // Initialize EXTI PC_13
    EXTI_init(BUTTON, FALL, 10);

    // PWM of 10 msec:  TIM2_CH2 (PA_1) 
    PWM_init(PWM, 20);          // 20 msec period -> 50 Hz 
    PWM_duty(PWM, 0.0f);        // 20% of duty
    // PWM_pulsewidth(PWM, 0.1111); //  a Pulse of 2msec =(duty=1/10=20%)
}



int main(void) {
    // Initialization --------------------------------------------------
    setup();    
    float duty_ratio = 0.025f;
    // Infinite Loop ---------------------------------------------------
    while(1){       
        if (flag == 1){                       
            duty_ratio +=0.005555f;
            if(duty_ratio > 0.125f) duty_ratio = 0.025f;
            PWM_duty(PWM, duty_ratio);    
            flag = 0;                    
        }
        if (initialize == 1){
            duty_ratio = 0.125f;
            PWM_duty(PWM, duty_ratio);    
            initialize = 0;
        }
    }
}

// TIM3 Update Interrupt Handler
void TIM3_IRQHandler(void){
    if(is_UIF(TIM3)){           // Check UIF(update interrupt flag)
        flag = 1;
        clear_UIF(TIM3);        // Clear TIM_UI flag
    }
}

void EXTI15_10_IRQHandler(void){
    if (is_pending_EXTI(BUTTON)){
        initialize = 1;
        clear_pending_EXTI(BUTTON);
    }
}