/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Jihoon Park
Created          : 05-03-2021
Modified         : 14-10-2026 
Language/ver     : C++ in VS Code

Description      : Stepper Library
/----------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "ecStepper2.h"


// Stepper Motor variable
static PinName_t stepperPins[4];
static volatile uint32_t _steps;
static volatile uint32_t _step_delay = 100;		
static const StateStepper_t *fsm;				// points at fsm_full or fsm_half (chosen in stepper_init)
static volatile uint32_t state = 0;				// current FSM state



// Output: A B A' B'
static const StateStepper_t fsm_Full[4] = {	
 {{S1,S3},{HIGH,HIGH,LOW,LOW}},	
 {{S2,S0},{LOW,HIGH,HIGH,LOW}},
 {{S3,S1},{LOW,LOW,HIGH,HIGH}},
 {{S0,S2},{LOW,LOW,HIGH,HIGH}}
};


static const StateStepper_t fsm_Half[8] = {  
	{{S1,S7},{1,0,0,0}},
	{{S2,S0},{1,1,0,0}},
	{{S3,S1},{0,1,0,0}},
	{{S4,S2},{0,1,1,0}},
	{{S5,S3},{0,0,1,0}},
	{{S6,S4},{0,0,1,1}},
	{{S7,S5},{0,0,0,1}},
	{{S0,S6},{1,0,0,1}},
};


// Initialization of Stepper Motor
void stepper_init(uint32_t mode, PinName_t *pinStepper){
	if (mode == HALF) 
		fsm = fsm_Half;
	else
		fsm = fsm_Full;

	//  GPIO Digital Out Initiation
	// For A, B, AN, BN

	for (int i=0; i<4; i++){
		stepperPins[i] = pinStepper[i];
		GPIO_init(stepperPins[i], OUTPUT);
		GPIO_ospeed(stepperPins[i], 10);
	}
}

// Converts Motor [rpm] to step delay in [msec]
void stepper_speed (uint32_t speedRPM){      // rpm
		_step_delay = 60*1000/(STEP_PER_REV*speedRPM); 		//in [msec]	
		// [usec] can be used for a higher accuracy
		// But needs delay_us() 
}


// Run Stepper Motor for given steps and direction
void stepper_step(uint32_t steps, uint32_t direction){
	// Exit if stepper_init() not called 
	if (fsm == 0) return;
	_steps = steps;

	// run for step size: 
	for (uint32_t i = 0; i < _steps; i++){
		// Update Present State
		state = fsm[i].next[direction];

		// Output of Present State
		stepper_out(state);
	
		// Delay for steppermotor speed
		delay_ms(_step_delay);
	}
}

// Stepper Motor Output for given state
void stepper_out(uint32_t state){
	
	// stepperPins[0]=A, stepperPins[1]=B, ...
	// out[0]=A, out[1]=B, ...
	GPIO_write(stepperPins[0], fsm[state].out[0]);
	GPIO_write(stepperPins[1], fsm[state].out[1]);
	GPIO_write(stepperPins[2], fsm[state].out[2]);
	GPIO_write(stepperPins[3], fsm[state].out[3]);	
}


// Stop Stepper Motor
void stepper_stop(void) {
    _steps = 0;    
    
	// All pins DigitalOut '0'
	GPIO_write(stepperPins[0], LOW);
	GPIO_write(stepperPins[1], LOW);
	GPIO_write(stepperPins[2], LOW);
	GPIO_write(stepperPins[3], LOW);	
}



