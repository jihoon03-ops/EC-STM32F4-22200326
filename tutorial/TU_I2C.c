/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Jihoon Park
Created          : 10-26-2026
Modified         : 11-14-2026 
Language/ver     : C in VS Code

Description      : Tutorial - I2C temperature sensor (LM75)
                   SCL = PB_8,  SDA = PB_9,  device address = 0x4C
/----------------------------------------------------------------*/
#include <stdio.h>
#include "ecRCC2.h"
#include "ecSysTick2.h"
#include "ecUART2.h"
#include "ecI2C2.h"


uint8_t temp_data[2];
float   temp = 0;
int     err  = 0;

// Initialiization
void setup(void)
{
	RCC_PLL_init();			// System Clock = 84MHz
	SysTick_init();
	USART2_init();			// USB serial init
	I2C1_init();			// SCL = PB_8,  SDA = PB_9
}


int main(void) {
	// Initialiization --------------------------------------------------------
	setup();

	// Does the sensor answer ?
	err = I2C1_write(LM75_ADDR, LM75_REG_TEMP);
	if(err)	printf("Sensor NOT found. Check the wiring\r\n");
	else	printf("Sensor found at 0x%02X\r\n", LM75_ADDR);

	// Inifinite Loop ----------------------------------------------------------
	while(1){
		// Method 1 : read 1 byte -> whole degrees only
		I2C1_write(LM75_ADDR, LM75_REG_TEMP);		// select the register
		I2C1_read(LM75_ADDR, temp_data, 1);			// read it back
		printf("Method 1 : %d C \r\n", (int8_t)temp_data[0]);

		// Method 2 : read 2 bytes -> 1 LSB = 1/256 C, so 0.125 C on this part.
		//            Method 1 drops the fraction, so it reads up to 1 C LOW
		//            (0xFF,0x80 is -0.5 C but Method 1 shows -1 C).
		// I2C1_write(LM75_ADDR, LM75_REG_TEMP);
		// I2C1_read(LM75_ADDR, temp_data, 2);
		// temp = (int16_t)((temp_data[0] << 8) | temp_data[1]) / 256.0f;
		// printf("Method 2 : %.2f C \r\n", temp);

		delay_ms(1000);
	}
}