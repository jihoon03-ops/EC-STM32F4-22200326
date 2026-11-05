#include "ecSTM32F4v2.h"  
#include <string.h>      
#include <stdio.h>       

#define MAX_BUF 20       // Maximum buffer size for incoming serial strings (includes space for null terminator)
#define END_CHAR 13      // ASCII code 13: Carriage Return ('\r') used as frame delimiter
#define LED_PIN PA_5     // Onboard LED connected to Port A, Pin 5

// --- PC UART Variables (USART2) ---
static volatile uint8_t buffer_PC[MAX_BUF] = {0};   // Temporary RX buffer for incoming PC characters
static volatile uint8_t PC_string[MAX_BUF] = {0};   // Completed string buffer ready for processing in main()
static volatile uint8_t PC_data = 0;                // Holds single byte read from USART2 (PC)

// --- Secondary MCU UART Variables (USART1) ---
static volatile uint8_t buffer_MCU2[MAX_BUF] = {0}; // Temporary RX buffer for incoming MCU2 characters
static volatile uint8_t MCU2_string[MAX_BUF] = {0}; // Completed string buffer ready for processing in main()
static volatile uint8_t MCU2_data = 0;              // Holds single byte read from USART1 (MCU2)

// --- Buffer Indexing & Synchronization Flags ---
static volatile int idx = 0;                // Current write index for PC buffer
static volatile int idx_1 = 0;              // Current write index for MCU2 buffer
static volatile int bReceive = 0;            // Flag: set to 1 when a complete frame is received from PC
static volatile int bReceive_1 = 0;          // Flag: set to 1 when a complete frame is received from MCU2

// --- Error Status Flags ---
static volatile int err_PC_overflow = 0;    // Flag: set to 1 when PC input exceeds MAX_BUF capacity
static volatile int err_MCU2_overflow = 0;  // Flag: set to 1 when MCU2 input exceeds MAX_BUF capacity

/**
 * @brief Initializes core clocks, timers, UART channels, and GPIO pins.
 */
void setup(void){
    RCC_PLL_init();                // Configure system clock using PLL (High Performance)
    SysTick_init();                // Initialize SysTick timer for time-base/delays

    // Configure USART2: USB Serial connection to PC (9600 baud)
    USART2_init();
    USART2_baud(BAUD_9600);

    // Configure USART1: Serial connection to remote MCU2 (9600 baud)
    USART1_init();
    USART1_baud(BAUD_9600);

    // Configure PA_5 as digital output for LED control
    GPIO_init(LED_PIN, OUTPUT);
}

/**
 * @brief Main application loop monitoring flags updated by UART interrupt handlers.
 */
int main(void){
    setup();
    printf("MCU Initialized\r\n");

    while(1){
        // Check if a complete message frame has arrived from the PC
        if (bReceive == 1){
            printf("Send message: %s\r\n", PC_string);
            bReceive = 0; // Clear flag after handling
        }
        // Check if a complete message frame has arrived from MCU2
        else if (bReceive_1 == 1){
            printf("Message received: %s\r\n", MCU2_string);
            bReceive_1 = 0; // Clear flag after handling
        }

        // Display and clear buffer overflow errors
        if (err_PC_overflow) {
            printf("ERROR : Too long string from PC\r\n");
            err_PC_overflow = 0;
        }
        if (err_MCU2_overflow) {
            printf("ERROR : Too long string from MCU2\r\n");
            err_MCU2_overflow = 0;
        }
    }
}

/**
 * @brief Interrupt Service Routine for USART2 (PC Communication).
 *        Fires every time a byte is received over USB serial.
 */
void USART2_IRQHandler(void){ 
    if(is_USART2_RXNE()){              // Verify Receive Data Register Not Empty flag
        PC_data = USART2_read();        // Read character from PC
        USART2_write(&PC_data, 1);       // Echo character back to PC terminal for live typing feedback

        // Check for frame delimiter ('\r') indicating string end
        if (PC_data == END_CHAR) {
            bReceive = 1;               // Set ready flag for main loop display
            
            // Copy buffered content into string container
            memset((void*)PC_string, 0, MAX_BUF);
            memcpy((void*)PC_string, (void*)buffer_PC, idx);
            
            // Append delimiter and forward complete message to MCU2 over USART1
            buffer_PC[idx] = END_CHAR;
            USART1_write((uint8_t*)buffer_PC, idx + 1); 

            // Clear temporary buffer and reset pointer index
            memset((void*)buffer_PC, 0, MAX_BUF);
            idx = 0;
        }
        // Store byte if space remains (leaves 1 byte room for null terminator)
        else if (idx < MAX_BUF - 1) { 
            buffer_PC[idx++] = PC_data;
        }
        // Handle buffer overflow if input exceeds buffer limit before delimiter
        else { 
            idx = 0;
            memset((void*)PC_string, 0, MAX_BUF);
            memset((void*)buffer_PC, 0, MAX_BUF);
            err_PC_overflow = 1;        // Trigger overflow error flag
        }
    }
}

/**
 * @brief Interrupt Service Routine for USART1 (MCU2 Communication).
 *        Fires every time a byte is received from the secondary microcontroller.
 */
void USART1_IRQHandler(void){ 
    if(is_USART1_RXNE()){              // Verify Receive Data Register Not Empty flag
        MCU2_data = USART1_read();      // Read character from MCU2
        USART2_write(&MCU2_data, 1);    // Pass-through: echo MCU2 character to PC terminal

        // Check for frame delimiter ('\r') indicating string end
        if (MCU2_data == END_CHAR){
            bReceive_1 = 1;             // Set ready flag for main loop display
            
            // Copy buffered content into string container
            memset((void*)MCU2_string, 0, MAX_BUF);
            memcpy((void*)MCU2_string, (void*)buffer_MCU2, idx_1);
            
            // Clear temporary RX buffer and reset index pointer
            memset((void*)buffer_MCU2, 0, MAX_BUF);
            idx_1 = 0;
        }
        // Accumulate byte into buffer
        else if (idx_1 < MAX_BUF - 1) { 
            buffer_MCU2[idx_1++] = MCU2_data;

            // Immediate byte parsing: Toggle onboard LED based on incoming character commands
            if (MCU2_data == 'h' || MCU2_data == 'H'){
                GPIO_write(LED_PIN, HIGH); // Turn LED ON
            }
            else if (MCU2_data == 'l' || MCU2_data == 'L'){
                GPIO_write(LED_PIN, LOW);  // Turn LED OFF
            }
        }
        // Handle buffer overflow condition
        else { 
            idx_1 = 0;
            memset((void*)MCU2_string, 0, MAX_BUF);
            memset((void*)buffer_MCU2, 0, MAX_BUF);
            err_MCU2_overflow = 1;      // Trigger overflow error flag
        }
    }
}
