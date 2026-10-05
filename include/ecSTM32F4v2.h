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
#include "ecPinNames.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"
//#include "ecTIM2.h"
//#include "ecPWM2.h"
//#include "ecStepper2.h"
//#include "ecADC2.h"
//#include "ecUART2.h"

#endif

// #define ...........
#define SW1_PIN    PD_2			//EVAL board JKIT SW1(RESET)
#define SW2_PIN    PA_4			//EVAL board JKIT SW2(PAUSE)
PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};      //7-segment DOUT
#define Selected_FND     PA_10    //selected 7-Segment Display  


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
        // Initialize GPIOA_4 for Input Button
    GPIO_init(SW2_PIN, INPUT);  // INPUT for EVAL board
    GPIO_pupd(SW2_PIN, PULLUP);  // PULL-UP for EVAL board
    
    // Initialize GPIOD_2 for Input Button
    GPIO_init(SW1_PIN, INPUT);  // INPUT for EVAL board
    GPIO_pupd(SW1_PIN, PULLUP);  // PULL-UP for EVAL board  

    // Initialize EXTI PA_4/ PD_2
    EXTI_init(SW2_PIN, FALL, 10);	
    EXTI_init(SW1_PIN, FALL, 9);

    // Initialize FND pins
    FND_init(pinFND);
    for(int i = 0; i<8; i++){
        GPIO_otype(pinFND[i], LOW);                 // 0: Push-Pull
        GPIO_pupd(pinFND[i], N0_PULLUP_PULLDOWN);   // no pull up pull down
        GPIO_ospeed(pinFND[i], 01);                 // 01: Medium speed
    }

    // Initialize FND selection Pin
    GPIO_init(Selected_FND, OUTPUT);
    GPIO_otype(Selected_FND, LOW);                 // 0: Push-Pull

}


 