/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Jihoon Park
Created          : 10-23-2026
Modified         : 11-14-2026 
Language/ver     : C in VS Code

Description      : Tutorial - ADC timer-triggered + interrupt, regular group (ecADC2)

/----------------------------------------------------------------*/
#include "ecSTM32F4v2.h"
#include "ecADC2.h"

//Analog Sensor parameter//
volatile uint32_t value1, value2;
volatile uint32_t seqIdx = 0;           // EOC fires once per conversion
PinName_t seqCHn[2] = {PB_0, PB_1};

void setup(void);

int main(void) {
    // Initialiization --------------------------------------------------------
    setup();

    // Inifinite Loop ----------------------------------------------------------
    while(1){
        printf("value1 = %lu \r\n",value1);
        printf("value2 = %lu \r\n",value2);
        printf("\r\n");

        delay_ms(1000);
    }
}

// Initialiization
void setup(void)
{
    RCC_PLL_init();         // System Clock = 84MHz
    USART2_init();           // UART2 Init
    SysTick_init();         // SysTick Init

    // ADC Init  Default: SW trigger, single conversion, no interrupt
    ADC_init(PB_0);
    ADC_init(PB_1);

    // ADC channel sequence setting
    ADC_sequence(seqCHn, 2);

    // HW trigger : TIM3 TRGO @ 1msec, enables EOC interrupt
    ADC_trigger_init(TIM3, 1, ADC_RISE);
}


void ADC_IRQHandler(void){
    if(is_ADC_OVR()) clear_ADC_OVR();
    if(is_ADC_EOC()){       // EOC per conversion : SQ1, then SQ2
        if(seqIdx == 0) value1 = ADC_read();
        else            value2 = ADC_read();
        seqIdx ^= 1;
    }
}