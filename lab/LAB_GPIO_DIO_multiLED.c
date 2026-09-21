/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Jihoon Park
Created          : 19-09-2026
Modified         : 17-09-2026 
Language/ver     : C++ in VS Code

Description      : turn on the LED 0~3 only one at a time by pressing the button. 
/----------------------------------------------------------------*/

#include "ecRCC2.h"
#include "ecGPIO2.h"

#define SW2_PIN PA_4

PinName_t led_pin[4] = {PB_12, PB_13, PB_14, PB_15};


// Initialiization 
void setup(void) {
	RCC_HSI_init();
	// initialize the pushbutton pin as an input:
	GPIO_init(SW2_PIN, INPUT);
    GPIO_pupd(SW2_PIN, PULLUP);  
	// initialize the LED pin as an output:
    for (unsigned int i = 0; i<4; i++)
    {
        GPIO_init(led_pin[i], OUTPUT);
        GPIO_pupd(led_pin[i], PULLUP);
        GPIO_otype(led_pin[i], HIGH); // 01: open drain
        GPIO_ospeed(led_pin[i], 01); // 01: Medium speed
    }      
}
	
int main(void) { 
 	setup();
	int buttonState=0;
	unsigned int j = 0;

	while(1){
		// check if the pushbutton is pressed. Turn LED on/off accordingly:
		buttonState = GPIO_read(SW2_PIN);
		if(buttonState == 0)	{
            GPIO_write(led_pin[j], LOW);
            j+=1;
            if (j==4) j = 0;
            GPIO_write(led_pin[j], HIGH);
        }
		else {		
        GPIO_write(led_pin[j], HIGH);
        }
		delay_ms_HSI(100);             					// delay 100 ms
	}
}