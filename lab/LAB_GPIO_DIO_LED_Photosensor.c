/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Jihoon Park
Created          : 05-03-2021
Modified         : 17-09-2026 [WRITE THE DATE!!!!]
Language/ver     : C++ in VS Code

Description      : photosensor LAB. Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/

#include "ecRCC2.h"
#include "ecGPIO2.h"

#define LED_PIN PB_12
#define BUTTON_PIN PA_0


// Initialiization 
void setup(void) {
	RCC_HSI_init();
	// initialize the pushbutton pin as an input:
	GPIO_init(BUTTON_PIN, INPUT);  
	GPIO_pupd(BUTTON_PIN, PULLUP);
	// initialize the LED pin as an output:
	GPIO_init(LED_PIN, OUTPUT);
	GPIO_pupd(LED_PIN, PULLUP);
	GPIO_otype(LED_PIN, HIGH);
	GPIO_ospeed(LED_PIN, 01); //01: Medium speed
}
	
int main(void) { 
 	setup();
	int buttonState=0;
	
	while(1){
		// check if the pushbutton is pressed. Turn LED on/off accordingly:
		buttonState = GPIO_read(BUTTON_PIN);
		if(buttonState)	GPIO_write(LED_PIN, LOW);
		else 		GPIO_write(LED_PIN, HIGH);
		delay_ms_HSI(100);             					// delay 100 ms
	}
}