#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"
#include "ecStepper2.h"

#define BUTTON_PIN  PC_13
<<<<<<< HEAD


// ( A, B,  AN,  BN)
//PinName_t pinStepper[4]    = {PC_5,PC_6,PC_7,PC_8};
PinName_t pinStepper[4] = {PB_10, PB_4, PB_5, PB_3};


=======
#define EC_DIN      0


// ( A, B,  AN,  BN)
PinName_t pinStepper[4]    = {PB_10,PB_4,PB_5,PB_3};
>>>>>>> 354b7821be33fa350ade9b0c40df756a249ff568

// Initialiization 
void setup(void){	
	RCC_PLL_init();                                 // System Clock = 84MHz
	SysTick_init();                                 // Systick init
	
<<<<<<< HEAD
	GPIO_init(BUTTON_PIN, INPUT);           		// GPIOC pin13 initialization
    EXTI_init(BUTTON_PIN, FALL, 0);           		// External Interrupt Setting

	stepper_init(HALF, pinStepper); 				// Stepper GPIO pin initialization
	stepper_speed(10);                        		//  set stepper motor speed
=======
	GPIO_init(BUTTON_PIN, EC_DIN);           		// GPIOC pin13 initialization
    EXTI_init(BUTTON_PIN, FALL, 0);           		// External Interrupt Setting

	stepper_init(FULL, pinStepper); 				// Stepper GPIO pin initialization
	stepper_speed(2);                          		//  set stepper motor speed
>>>>>>> 354b7821be33fa350ade9b0c40df756a249ff568
}


int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
<<<<<<< HEAD
	uint32_t rev=2;
=======
	uint32_t rev=1;
>>>>>>> 354b7821be33fa350ade9b0c40df756a249ff568
	uint32_t steps=STEP_PER_REV*rev;
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		stepper_step(steps, DIR_CW);  // (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)
		delay_ms(2000);
		stepper_step(steps, DIR_CCW);  // (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)
		delay_ms(2000);
	}
}


<<<<<<< HEAD
=======

>>>>>>> 354b7821be33fa350ade9b0c40df756a249ff568
void EXTI15_10_IRQHandler(void) {  
	if (is_pending_EXTI(BUTTON_PIN)) {
		stepper_stop();
		clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
	}
}