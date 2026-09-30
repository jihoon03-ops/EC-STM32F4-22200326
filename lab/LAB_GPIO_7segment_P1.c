#include "stm32f4xx.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"

PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
PinName_t selectFND[4] = {PA_10, PA_11, PC_4, PC_3};

void setup(void){
    // Initialize System Clock
    RCC_HSI_init();    
    // Initialize FND pins
    FND_init(pinFND);
    // Initialize FND_select pins
    FND_select_init(selectFND);
    for(int i = 0; i<4; i++){			// changing all pins in selectFND[4]
        GPIO_otype(selectFND[i], LOW); 	// Push-Pull
    }
    for(int i = 0; i<8; i++){
        GPIO_otype(pinFND[i], LOW); 	// Push-Pull
        GPIO_ospeed(pinFND[i], 01); 	// Medium speed
    }
};

int main(void) {
    setup();
    uint8_t numDisplay1  = 0;
    uint8_t numDisplay2  = 5;
    uint8_t selectFND1  = 0;
    uint8_t selectFND2  = 1;

    while (1) {
        FND_select(selectFND1);			// PIN PA_10, ODR--> HIGH (means selecting PIN PA_10)
        FND_display(numDisplay1);		// display '0'
        delay_ms_HSI(1);             	// delay 1ms
        FND_select(selectFND2);			// PIN PA_11, ODR--> HIGH (means selecting PIN PA_11)
        FND_display(numDisplay2);		// display '5'
        delay_ms_HSI(1);				// delay 1ms
    }
}