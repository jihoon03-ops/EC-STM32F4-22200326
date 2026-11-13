/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Jihoon Park
Created          : 11-11-2026 
Language/ver     : C in VS Code

Description      : LAB - Ultrasonic distance sensor

                Measures the signal with ICAP of  PB_6 (TIM4_CH1).                   
                    IC1 = rising edge, IC2 = falling edge   (TI1 -> IC1, IC2)
/----------------------------------------------------------------*/

#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecSysTick2.h"
#include "ecTIM2.h"
#include "ecICAP2.h"
#include "ecPWM2.h"
#include "ecUART2.h"

#define ICAP_PIN    PB_6        // TIM4_CH1
#define PWM_PIN     PA_6        // TIM3_CH1

uint32_t pwm_period_ms=100;
uint32_t uTick=100;
uint32_t timer_arr  = 65536;    // ticks per counter wrap (ARR+1)

volatile uint32_t ovf_cnt = 0;      //counts overflows
volatile uint32_t cap_prev   = 0;   // CCR of the previous rising edge
volatile uint32_t cap_curr    = 0;  // CCR of the current rising edge
volatile uint32_t counts = 0;       // [pulses]
volatile float timeInterval = 0;    // [usec]
volatile float distance = 0;        // [cm]


void setup(void){
    RCC_PLL_init();
    SysTick_init();
                     
    USART_init(USART2, PA_2, PA_3, 9600);

    PWM_init(PWM_PIN, pwm_period_ms);
    PWM_duty(PWM_PIN, 0.001f);
    // PWM pin configuration
    GPIO_pupd(PWM_PIN, NO_PULLUP_PULLDOWN);
    GPIO_otype(PWM_PIN, PUSH_PULL);
    GPIO_ospeed(PWM_PIN, FAST_SPEED);

    // Input capture  rising edge TIn=ICn, tick = uTick usec    
    ICAP_init(ICAP_PIN, IC_RISE);
    ICAP_ICn_init(ICAP_PIN, IC_FALL, IC_2);     //TI1 -> IC2, falling
    ICAP_tick(ICAP_PIN, uTick);         

    timer_arr=TIM4->ARR + 1;
}

int main(void){
    setup();
    printf("LAB_Ultrasonic_distance_sensor\r\n"); 

    while(1){
        printf("distance = %.2f cm\r\n", distance); //print distance on PC every 2second.         
        delay_ms(2000);
    }
}


void TIM4_IRQHandler(void){
    // Counter overflow 
    if(is_UIF(TIM4)){       // when overflow happens
        ovf_cnt++;          // count overflow
        clear_UIF(TIM4);    // clear UIF bit
    }

    // Rising edge captured on IC1
    if(is_CCIF(TIM4, IC_1)){                    // IC1 : rising edge, SAME pin (TI1)
        cap_prev = ICAP_read(ICAP_PIN, IC_1);   // capture CCR value
        clear_CCIF(TIM4,IC_1);                  // clear CCIF bit              
    }
    // Falling edge captured on IC2
    if(is_CCIF(TIM4, IC_2)){                    // IC2 : falling edge, SAME pin (TI1)       
        cap_curr = ICAP_read(ICAP_PIN, IC_2);               // capture CCR value

        // Ticks between the two edges, then scaled to usec.        
        counts = (cap_curr-cap_prev) + (ovf_cnt*timer_arr); // calculate num of pulses
        timeInterval=counts*uTick;                          // calculate time interval 
        distance = timeInterval/58;                         // derive distance 

        ovf_cnt    = 0;                                     // reset overflow counting
        clear_CCIF(TIM4, IC_2);                             // clear CCIF bit 
    }   
}
