/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Jihoon Park
Created          : 05-03-2021
Modified         : 05-10-2026
Language/ver     : C++ in VS Code

Description      : LAB_EXTI
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecSysTick2.h"
#include "ecEXTI2.h"

uint8_t numDisplay = 0;

// void FND_Pause(PinName_t pinName);  // in ecGPIO2.h
void FND_Pause(void){
    delay_ms(1000);
}

void FND_RESET(void){
    numDisplay = 9;
}

// Initialiization 
void setup(void)
{
    MCU_init();
}


// MAIN  ----------------------------------------
int main(void) {
	setup();
    
    GPIO_write(Selected_FND, HIGH);

	while (1){
        FND_display(numDisplay);
        delay_ms(1000);
        numDisplay += 1;
        if (numDisplay == 10) numDisplay = 0;
    }
}

void EXTI4_IRQHandler(void) {
	if (is_pending_EXTI(SW2_PIN)) {   
		FND_Pause();
		clear_pending_EXTI(SW2_PIN);
	}
}

void EXTI2_IRQHandler(void) {
    if (is_pending_EXTI(SW1_PIN)){
        FND_RESET();
        clear_pending_EXTI(SW1_PIN);
    }
}
