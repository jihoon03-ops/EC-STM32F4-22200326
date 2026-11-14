/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Jihoon Park
Created          : 10-23-2026
Modified         : 11-14-2026 
Language/ver     : C in VS Code

Description      : Tutorial - ADC polling, injected group (ecADC2)

/----------------------------------------------------------------*/
#include "ecSTM32F4v2.h"
#include "ecADC2.h"

//Analog Sensor parameter//
uint32_t value1, value2;
PinName_t seqCHn[2] = {PB_0, PB_1};

void setup(void);

int main(void) {
    // Initialiization --------------------------------------------------------
    setup();

    // Inifinite Loop ----------------------------------------------------------
    while(1){
        value1 = JADC_read_poll();      // one start converts the sequence
        value2 = JADC_read(2);          // JDR2 already holds conversion 2

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
}