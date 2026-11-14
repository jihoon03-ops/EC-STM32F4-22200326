/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Jihoon Park
Created          : 10-23-2026
Modified         : 11-14-2026 
Language/ver     : C in VS Code

Description      : Tutorial - ADC timer-triggered + interrupt, injected group (ecADC2)

/----------------------------------------------------------------*/
#include "ecSTM32F4v2.h"
#include "ecADC2.h"

//Analog Sensor parameter//
volatile uint32_t value1, value2;
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

    // JADC Init  Default: SW trigger, no interrupt
    JADC_init(PB_0);
    JADC_init(PB_1);

    // JADC channel sequence setting
    JADC_sequence(seqCHn, 2);

    // HW trigger : TIM5 TRGO @ 1msec - enables JEOC interrupt
    JADC_trigger_init(TIM5, 1, ADC_RISE);
}


void ADC_IRQHandler(void){
    if(is_ADC_JEOC()){      // one JEOC after the whole sequence
        value1 = JADC_read(1);
        value2 = JADC_read(2);
        clear_ADC_JEOC();
    }
}