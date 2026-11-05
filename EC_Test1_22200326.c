
#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"
#include "ecStepper2.h"
#include "ecUART2.h"

#define SW1_PIN             PD_2
#define SW2_PIN             PA_4
#define PHOTO_SENSER_PIN    PA_0
#define LED_0               PB_12


PinName_t pinStepper[4]    = {PC_5, PC_6, PC_7, PC_8};
PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
PinName_t selectFND[4] = {PA_10, PA_11, PC_4, PC_3};


void setup(void){
      // CLOCK PLL 84MHz
    RCC_PLL_init();
    
    // SysTick 1msec
    SysTick_init();    
    
    // Button 
    GPIO_init(SW1_PIN, INPUT);
    GPIO_pupd(SW1_PIN, PULLUP);
    EXTI_init(SW1_PIN, FALL, 9);

    GPIO_init(SW2_PIN, INPUT);
    GPIO_pupd(SW2_PIN, PULLUP);
    EXTI_init(SW2_PIN, FALL, 10);	

    GPIO_init(PHOTO_SENSER_PIN, INPUT);
    GPIO_pupd(PHOTO_SENSER_PIN, PULLUP);
    
    //LED 
    GPIO_init(LED_0, OUTPUT);    

    stepper_init(FULL, pinStepper); 				// Stepper GPIO pin initialization
	stepper_speed(10);                          		//  set stepper motor speed
        
    // 2. Initialize USART2 (PC connection - 9600 baud)
    USART2_init();
    USART2_baud(BAUD_9600);
    
    for(int i = 0; i<8; i++){
        GPIO_init(pinFND[i], OUTPUT);
        GPIO_otype(pinFND[i], PUSH_PULL); 	// Push-Pull
    } 

    for(int i = 0; i<4; i++){
        GPIO_init(selectFND[i], OUTPUT);
        GPIO_otype(selectFND[i], PUSH_PULL); 	// Push-Pull
    } 
}

int main(void) {
    setup();

    uint32_t rev= 2;
	uint32_t steps = STEP_PER_REV * rev;

    uint8_t numDisplay1  = 0;
    uint8_t selectFND1  = 0;

    GPIO_write(LED_0, HIGH);
    FND_select(selectFND1);			// PIN PA_10, ODR--> HIGH (means selecting PIN PA_10)
    FND_display(numDisplay1);		// display '0'
    
    

	// Inifinite Loop ----------------------------------------------------------
	while(1){
        // GPIO_write(LED_0, HIGH);
        // FND_select(selectFND1);			// PIN PA_10, ODR--> HIGH (means selecting PIN PA_10)
        // FND_display(numDisplay1);		// display '0'
		stepper_step(steps, DIR_CW);  // (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)
        
        delay_ms(1);
        
	}

}