/*----------------------------------------------------------------@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Jihoon Park
Created          : 10-13-2026
Modified         : 11-01-2026 
Language/ver     : C in VS Code

Description      : LAB - PWM - RC(servo motor)
                   PA_1 (TIM2_CH2, servo motor input signal) : 50 Hz, duty sweep 2.5 -> 12.5%                   
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

volatile uint8_t flag = 0;          // 500msec flag
volatile uint8_t initialize = 0;    // initialize flag
volatile uint8_t flag_decrease = 0; // decrease angle flag

// Initialiization 
void setup(void) {  
    RCC_PLL_init();             // PLL: 84MHz
    SysTick_init();           

    TIM_UI_init(TIM3, 500);     // UEV every 500 msec

    GPIO_init(BUTTON, INPUT);   // INPUT for EVAL board
    GPIO_pupd(BUTTON, PULLUP);  // PULL-UP for EVAL board  
    
    EXTI_init(BUTTON, FALL, 10);// Initialize EXTI PC_13

    PWM_init(PWM, 20);          // PWM of 20 msec(50Hz):  TIM2_CH2 (PA_1) 
    PWM_duty(PWM, 0.025f);      // duty ratio: 2.5%
}


int main(void) {
    // Initialization --------------------------------------------------
    setup();
    float duty_ratio = 0.025f;          // initialize duty ratio memory
    // Infinite Loop ---------------------------------------------------
    while(1){    
        PWM_duty(PWM, duty_ratio);          // apply the renewed duty ratio   
        if (flag){                          // activates every 500msec(TIM3 period) 
            if (flag_decrease==0){                     
                duty_ratio +=0.0055556f;    // +0.0055556(rounded value) increase matches with 10[degree] increase
            }
            else{
                duty_ratio -= 0.0055556f;   // -0.0055556(rounded value) decrease matches with 10[degree] decrease
            }
            if(duty_ratio >= 0.125f){       // duty ratio upper limit: 0.125
                flag_decrease = 1;          // set flag for decrease duty ratio
                duty_ratio = 0.125f;        // set duty ratio as exact 0.125
            }
            else if(duty_ratio <= 0.025f){  // duty ratio bottom limit: 0.025
                flag_decrease = 0;          // reset flag for decrease duty ratio
                duty_ratio = 0.025f;        // set duty ratio as exact 0.025
            }
            flag = 0;                       // reset flag
        }
        if (initialize == 1){               // when button press happens 
            duty_ratio = 0.025f;            // duty ratio reset: 0.025
            flag_decrease = 0;              // reset flag for decrease duty ratio
            initialize = 0;                 // reset initialize flag
        }
    }    
}


void TIM3_IRQHandler(void){     // set flag every 500msec
    if(is_UIF(TIM3)){           // Check UIF(update interrupt flag)
        flag = 1;               // set flag 
        clear_UIF(TIM3);        // Clear TIM_UI flag
    }
}

void EXTI15_10_IRQHandler(void){    // when button is pressed
    if (is_pending_EXTI(BUTTON)){   // Check button pending bit
        initialize = 1;             // set initialize flag
        clear_pending_EXTI(BUTTON); // Clear button pending bit
    }
}