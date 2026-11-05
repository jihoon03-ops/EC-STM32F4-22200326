
#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"
#include "ecStepper2.h"
#include "ecUART2.h"

/* --- Configuration Constants --- */
#define END_CHAR    13    // ASCII Carriage Return ('\r') signal character
#define LED_PIN     PA_5  // On-board LD2 LED output pin (Nucleo-F411RE)

// Stepper Motor 4-Phase Drive Control Pins: [Phase A, Phase B, Phase A', Phase B']
PinName_t pinStepper[4] = {PB_10, PB_4, PB_5, PB_3};

/* --- Volatile Global Flags (Shared between ISR and Main Loop) --- */
static volatile uint8_t BT_data = 0;      // Stores the latest byte received via Bluetooth
static volatile uint8_t new_line = 0;     // Flag indicating Carriage Return received

// Movement Command Execution Flags
static volatile uint8_t Stepper_CW = 0;   // Flag to execute CW rotation
static volatile uint8_t Stepper_CCW = 0;  // Flag to execute CCW rotation
static volatile uint8_t Stepper_stop = 0; // Flag to execute emergency stop

// Step count required for 2 complete 360-degree revolutions
uint32_t steps = STEP_PER_REV * 2; 

/**
 * @brief  Initializes system clocks, peripherals, serial communications, and motor hardware.
 */
void setup(void){
    // System & Base Timer Initialization
    RCC_PLL_init();       // Set System Clock (SYSCLK) to 84MHz using PLL
    SysTick_init();       // Initialize SysTick timer for accurate time delays

    // USART1 Communication Setup (PA9: TXD, PA10: RXD) for HC-06 Bluetooth Module
    USART1_init();
    USART1_baud(BAUD_9600); // Standard baud rate for HC-06 module

    // Peripheral Initialization
    GPIO_init(LED_PIN, OUTPUT);           // Configure PA5 as digital output for LD2 LED
    stepper_init(FULL, pinStepper);       // Initialize stepper pins in Full-Step excitation mode
    stepper_speed(5);                     // Set rotational speed to 5 RPM (Revolutions Per Minute)
}

/**
 * @brief  Main Application Loop: Monitors motion flags set by ISR and executes stepper actions.
 */
int main(void){ 
    setup();
    printf("MCU Initialized\r\n");  

    while(1){
        // Print newline format to terminal if Carriage Return flag was set
        if (new_line){
            printf("\r\n");
            new_line = 0;
        }

        // Stepper Control State Machine (Polling Flags set by Interrupt Handler)
        if (Stepper_CW){
            stepper_step(steps, DIR_CW);  // Execute 2 revolutions Clockwise
            Stepper_CW = 0;               // Clear flag upon movement completion
        }
        else if (Stepper_CCW){
            stepper_step(steps, DIR_CCW); // Execute 2 revolutions Counter-Clockwise
            Stepper_CCW = 0;              // Clear flag upon movement completion
        }
        else if (Stepper_stop){
            stepper_stop();               // Stop stepping motor output pins immediately
            Stepper_stop = 0;             // Clear flag
        }
    }
}

/**
 * @brief  USART1 Interrupt Service Routine (ISR)
 * @note   Fired automatically whenever a new byte arrives on the RX line (PA10).
 */
void USART1_IRQHandler(void){       
    // Check if the RXNE (Read Data Register Not Empty) interrupt flag is set
    if(is_USART1_RXNE()){
        BT_data = USART1_read();         // Read incoming byte from USART RX buffer
        USART1_write(&BT_data, 1);       // Echo received byte back to host serial terminal

        /* --- LED Command Processing --- */
        if (BT_data == 'h' || BT_data == 'H'){
            GPIO_write(LED_PIN, HIGH);   // Turn ON onboard LED
        }
        else if (BT_data == 'l' || BT_data == 'L'){
            GPIO_write(LED_PIN, LOW);    // Turn OFF onboard LED
        }
        
        /* --- Stepper Motor Command Processing --- */
        else if (BT_data == 'J' || BT_data == 'j'){
            Stepper_CCW = 0;             // Cancel pending CCW request
            Stepper_stop = 0;            // Cancel pending stop request
            Stepper_CW = 1;              // Trigger CW rotation in main loop
        }
        else if (BT_data == 'K' || BT_data == 'k'){
            Stepper_CW = 0;              // Cancel pending CW request
            Stepper_stop = 0;            // Cancel pending stop request
            Stepper_CCW = 1;             // Trigger CCW rotation in main loop
        }
        else if (BT_data == 'P' || BT_data == 'p'){
            Stepper_CW = 0;              // Cancel pending CW request
            Stepper_CCW = 0;             // Cancel pending CCW request
            Stepper_stop = 1;            // Trigger emergency stop in main loop
        }
        
        /* --- Terminal Formatting Processing --- */
        else if (BT_data == END_CHAR){
            new_line = 1;                // Flag main loop to send newline
        }
    }
}