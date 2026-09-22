#include "stm32f4xx.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"

#define SW2_PIN PA_4

PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
PinName_t selectFND[4] = {PA_10, PA_11, PC_4, PC_3};


void setup(void){
    // Intialize System Clock
    RCC_HSI_init();    
    // Intialize pinFND pins
    FND_init(pinFND);
    for(int i = 0; i<8; i++){
        GPIO_otype(pinFND[i], LOW);                 // 0: Push-Pull
        GPIO_pupd(pinFND[i], N0_PULLUP_PULLDOWN);   // no pull up pull down
        GPIO_ospeed(pinFND[i], 01);                 // 01: Medium speed
    }
    // Intialize selectFND[1], PA_10 (FND_0)
    GPIO_init(selectFND[0], OUTPUT); // DOUT
    GPIO_otype(selectFND[0], LOW); //  0: Push-Pull
    // Intialize SW2_PIN pins
    GPIO_init(SW2_PIN, INPUT);    // DIN
    GPIO_pupd(SW2_PIN, PULLUP);   // 01: Pull-Up
};

int main(void) {
    setup();
    uint8_t buttonState = 0;
    uint8_t numDisplay = 0;
    GPIO_write(selectFND[0], HIGH);
  
    while (1) {
        buttonState = GPIO_read(SW2_PIN);
        if(buttonState==0){
            numDisplay +=1;
            if(numDisplay == 10) numDisplay=0;
            FND_display(numDisplay);
        }
        else{
            FND_display(numDisplay);
        }
        delay_ms_HSI(100);	
    }
}