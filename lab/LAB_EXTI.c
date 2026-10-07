/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Jihoon Park
Created          : 05-03-2021
Modified         : 05-10-2026
Language/ver     : C++ in VS Code

Description      : LAB_EXTI
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"


uint8_t numDisplay = 0;
volatile uint8_t set = 0;

// void FND_Pause(PinName_t pinName);  // in ecGPIO2.h
void FND_Pause(void){
    set ^= 1;           //if set == 0 , set = 1 (displaying same number on FND)
}                       //if set == 1 , set = 0 (count up number on FND)

void FND_RESET(void){
    numDisplay = 9;     //in most case, SW1_BUTTON is pushed at the delay_ms() in main(). 
}                       //because numDisplay+=1 is located after delay_ms(), numDisplay = 0 right away. displaying 0 on FND. 

// Initialiization 
void setup(void)
{
    MCU_init();
}


// MAIN  ----------------------------------------
int main(void) {
	setup();
    
    GPIO_write(Selected_FND, HIGH);     //activate Selected Pin

	while (1){
        FND_display(numDisplay);        //Display "numDisplay" on FND
        delay_ms(1000);                 //1000ms delay  
        if (set == 0)                   // if SW2_BUTTON is pushed once(set == 1), jump the following code. 
        {                               // if not(set == 0), activate the following code. 
            numDisplay += 1;                        //count up
            if (numDisplay == 10) numDisplay = 0;   //count up to 9 and go back to 0.
        }
    }
}

void EXTI4_IRQHandler(void) {
	if (is_pending_EXTI(SW2_PIN)) {     //read EXTI->PR of SW2_PIN
		FND_Pause();
		clear_pending_EXTI(SW2_PIN);    //clear EXTI->PR of SW2_PIN
	}
}

void EXTI2_IRQHandler(void) {
    if (is_pending_EXTI(SW1_PIN)){      //read EXTI->PR of SW1_PIN
        FND_RESET();
        clear_pending_EXTI(SW1_PIN);    //clear EXTI->PR of SW1_PIN
    }
}
