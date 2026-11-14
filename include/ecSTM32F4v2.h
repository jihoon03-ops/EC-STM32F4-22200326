//ecSTM32F4v2.h


/**
******************************************************************************
* @course   Embedded Controller- HGU
* @author	iiLAB
* @mod		2024-8-05 by YKKIM
* @brief	STM32F411 Library for EC
*
******************************************************************************
*/

#ifndef __EC_STM_H
#define __EC_STM_H

// STM built-In Library
#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "math.h"

// EC course Library
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecSysTick2.h"
#include "ecEXTI2.h"
#include "ecTIM2.h"
#include "ecICAP2.h"
#include "ecPWM2.h"
#include "ecUART2.h"
#include "ecADC2.h"
#include "ecI2C2.h"
//#include "ecStepper2.h"


#endif

// #define ...........
//#define LED_PIN     PA_5



// enum...........

void MCU_init(void){
    // CLOCK PLL 84MHz
    RCC_PLL_init();
    
    // SysTick 1msec
    SysTick_init();    
    
    // Button PC13
    // GPIO_init(PC_13, INPUT);
    // GPIO_pupd(PC_13, PULLUP);    
    
    // LED PA5
    // GPIO_init(PB_12, OUTPUT);    

    // TIMx Default Initialization
    // ...
    // PWM Default Initialization
    // ...        
    // USART Default Initialization
    // ...
    // LAB_EXTI Default Initialization
    // ...
}


 