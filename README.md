# EC-STM32F4-22200326

### Embedded Controller - STM32F411 Driver Library

Written by: Jihoon Park

Program: C/C++

IDE/Compiler: Keil uVision 5

OS: WIn10/11

MCU: STM32F411RE, Nucleo-64

**Table of Contents**

* [GPIO Digital In/Out](#gpio-digital-inout)
  * [Header File](#header-file)
  * [GPIO_init()](#gpio_init)
  * [GPIO_mode()](#gpio_mode)
  * [GPIO_write()](#gpio_write)
  * [GPIO_read()](#gpio_read)
  * [GPIO_ospeed()](#gpio_ospeed)
  * [GPIO_otype()](#gpio_otype)
  * [GPIO_pupdr()](#gpio_pupdr)
  * [Example Code](#example-code)
* [EXTI](#exti)
  * [Header File](#header-file-1)
  * [EXTI_init()](#exti_init)
  * [EXTI_enable](#exti_enable)
  * [EXTI_disable](#exti_disable)
  * [is_pending_EXTI](#is_pending_exti)
  * [clear_pending_EXTI](#clear_pending_exti)
  * [Example Code](#example-code-1)
* [Stepper](#stepper-motor)
  * [Header File](#header-file-2)
  * [stepper_init()](#stepper_init)
  * [stepper_speed()](#stepper_speed)
  * [stepper_step()](#stepper_step)
  * [stepper_out()](#stepper_out)
  * [stepper_stop()](#stepper_stop)
  * [Example Code](#example-code-2)
* [UART](#uart)
  * [Header File](#header-file-3)
  * [USART_init()](#usart_init)
  * [USART_baud()](#usart_baud)
  * [USART_pins()](#usart_pins)
  * [USART_clock_enable()](#usart_clock_enable)
  * [USART_write()](#usart_write)
  * [USART_read()](#usart_read)
  * [is_USART_RXNE()](#is_usart_rxne)
  * [USART_delay()](#usart_delay)
  * [Example Code](#example-code-3)
* [Timer](#timer)
  * [Header File](#header-file-4)
  * [TIM_UI_init()](#tim_ui_init)
  * [TIM_UI_init_us()](#tim_ui_init_us)
  * [TIM_UI_enable()](#tim_ui_enable)
  * [TIM_UI_disable()](#tim_ui_disable)
  * [is_UIF()](#is_uif)
  * [clear_UIF()](#clear_uif)
  * [TIM_init()](#tim_init)
  * [TIM_init_us()](#tim_init_us)
  * [TIM_period_ms()](#tim_period_ms)
  * [TIM_period_us()](#tim_period_us)
  * [TIM_clock_enable()](#tim_clock_enable)
  * [get_TIM_IRQn()](#get_tim_irqn)
  * [Example Code](#example-code-4)
* [PWM](#pwm)
  * [Header File](#header-file-5)
  * [PWM_init()](#pwm_init)
  * [PWM_init_us()](#pwm_init_us)
  * [PWM_duty()](#pwm_duty)
  * [PWM_pulsewidth()](#pwm_pulsewidth)
  * [PWM_pulsewidth_us()](#pwm_pulsewidth_us)
  * [PWM_init_config()](#pwm_init_config)
  * [PWM_mode_config()](#pwm_mode_config)
  * [PWM_pinmap()](#pwm_pinmap)
  * [Example Code](#example-code-5)
* [Input Capture](#input-capture)
  * [Header File](#header-file-6)
  * [ICAP_init()](#icap_init)
  * [ICAP_ICn_init()](#icap_icn_init)
  * [ICAP_tick()](#icap_tick)
  * [ICAP_read()](#icap_read)
  * [is_CCIF()](#is_ccif)
  * [clear_CCIF()](#clear_ccif)
  * [ICAP_pinmap()](#icap_pinmap)
  * [ICAP_filter()](#icap_filter)
  * [ICAP_ICn_select()](#icap_icn_select)
  * [Example Code](#example-code-6)
***

### GPIO Digital InOut



#### Header File

`#include "ecGPIO.h"`

```c++
// MODER
#define INPUT  		0x00
#define OUTPUT 		0x01
#define AF     		0x02
#define ANALOG 		0x03

// IDR & ODR
#define HIGH 		1
#define LOW  		0

// OSPEED
#define LOW_SPEED		0x00
#define MID_SPEED		0x01
#define FAST_SPEED		0x02
#define HIGH_SPEED		0x03

// OTYPER
#define PUSH_PULL 		0	// Push-pull
#define OPEN_DRAIN 		1 	// Open-Drain

// PUDR
#define NO_PUPD			0x00 	// No pull-up, pull-down
#define PULL_UP			0x01 	// Pull-up
#define PULL_DOWN 		0x02 	// Pull-down	
#define RESERVED 		0x03 	// Reserved

// PIN
#define LED_PIN 		5
#define BUTTON_PIN 		13

void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
void GPIO_mode(GPIO_TypeDef* Port, int pin, int mode);
void GPIO_write(GPIO_TypeDef *Port, int pin, int output);
int  GPIO_read(GPIO_TypeDef *Port, int pin);
void GPIO_ospeed(GPIO_TypeDef* Port, int pin, int speed);
void GPIO_otype(GPIO_TypeDef* Port, int pin, int type);
void GPIO_pupdr(GPIO_TypeDef* Port, int pin, int pupd);

```



#### GPIO\_init()

Initializes GPIO pins with default setting and Enables GPIO Clock. Mode: In/Out/AF/Analog

```c
void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **mode**: INPUT(0), OUTPUT(1), AF(02), ANALOG (03)

**Example code**

```c
GPIO_init(GPIOA, 5, OUTPUT);
GPIO_init(GPIOC, 13, INPUT); //GPIO_init(GPIOC, 13, 0);
```



#### GPIO\_mode()

Configures GPIO pin modes: In/Out/AF/Analog

```c
void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **mode**: INPUT (0), OUTPUT (1), AF(02), ANALOG (03)

**Example code**

```c
GPIO_mode(GPIOA, 5, OUTPUT);C
```



#### GPIO\_write()

Write the data to GPIO pin: High, Low

```C
write(GPIO_TypeDef *Port, int pin, int output);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **output**: LOW(0), HIGH(1)

**Example code**

```c
GPIO_write(GPIOA, 5, 1);  // 1: High
```



#### GPIO\_read()

Read the data from GPIO pin

```c
int  GPIO_read(GPIO_TypeDef *Port, int pin);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15

**Example code**

```c
GPIO_read(GPIOC, 13);
```



#### GPIO\_ospeed()

Configures output speed of GPIO pin : Low, Mid, Fast, High

```c
void GPIO_ospeed(GPIO_TypeDef* Port, int pin, int speed);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **speed**: LOW\_SPEED(0), MID\_SPEED(1), FAST\_SPEED(2) , HIGH\_SPEED(3)

**Example code**

```c
GPIO_ospeed(GPIOA, 5, 2);  // 2: FAST_SPEED
```



#### GPIO\_otype()

Configures output type of GPIO pin: Push-Pull / Open-Drain

```c
void GPIO_otype(GPIO_TypeDef* Port, int pin, int type);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **type**: PUSH\_PULL(0), OPEN\_DRAIN(1)

**Example code**

```c
GPIO_otype(GPIOA, 5, 0);  // 0: Push-Pull
```



#### GPIO\_pupdr()

Configures Pull-up/Pull-down mode of GPIO pin: No Pull-up, Pull-down/ Pull-up/ Pull-down/ Reserved

```c
void GPIO_pupdr(GPIO_TypeDef* Port, int pin, int pupd);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **pupd**: NO\_PUPD(0), PULL\_UP(1), PULL\_DOWN(2), RESERVED(3)

**Example code**

```c
GPIO_pupdr(GPIOA, 5, 0);  // 0: No Pull-up, Pull-down
```

#### Example Code

```c++
#include "ecSTM32F411.h"

#define LED_PIN 5
#define BUTTON_PIN 13

// Initialiization 
void setup(void) {
	RCC_PLL_init();
	SysTick_init();
	GPIO_init(GPIOA, LED_PIN, OUTPUT);    
}
	
int main(void) { 
	setup();
	
	while(1){
		delay_ms(500);  
		GPIO_write(GPIOA, LED_PIN, LOW);
		delay_ms(500);  
		GPIO_write(GPIOA, LED_PIN, HIGH);
	}
}
```

***

### EXTI

#### Header File

`#include "ecEXTI2.h"`

```C++
#define FALL 0
#define RISE 1
#define BOTH 2

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

void EXTI_init(PinName_t pinName, uint32_t trig_type,uint32_t priority);
void EXTI_enable(PinName_t pinName);
void EXTI_disable(PinName_t pinName);
uint32_t is_pending_EXTI(PinName_t pinName);
void clear_pending_EXTI(PinName_t pinName);

#ifdef __cplusplus
}
#endif /* __cplusplus */
	 
#endif // __EC_EXTI2_H

```



#### EXTI\_init()

Enable EXTI Clock with SYSCFG controller clock, 

Connect EXTI to the GPIO Port_y Pin_x, 

Select  Trigger edge (RISE, FALL, BOTH), 

Enable EXTI, with Not-Masked Interrupt Request, 

NVIC(IRQ) Setting

```c
void EXTI_init(PinName_t pinName, uint32_t trig_type,uint32_t priority);
```

**Parameters**

* **pinName**: Port and Pin number, PA_0 ~ PH_1
* **trig_type**: FALL(0), RISE(1), BOTH(2)
* **priority**: 0 ~ 15

**Example code**

```c
EXTI_init(PB_12, FALL, 10);
```



#### EXTI\_enable()

unmask interrupt request from a specific pin.  

```c
void EXTI_enable(PinName_t pinName);
```

**Parameters**

* **pinName**: Port and Pin number, PA_0 ~ PH_1

**Example code**

~~~c
EXTI_enalbe(PB_12); // enable EXTI from PB_12
~~~



#### EXTI\_disable()

mask interrupt request from a specific pin.  

```c
void EXTI_disable(PinName_t pinName);
```

**Parameters**

* **pinName**: Port and Pin number, PA_0 ~ PH_1

**Example code**

~~~c
EXTI_disalbe(PB_12); // disable EXTI from PB_12
~~~



#### is_pending_EXTI()

read and return the pending bit of a specific pin. 

```c 
uint32_t is_pending_EXTI(PinName_t pinName);
```

**Parameters**

- **pinName**: Port and Pin number, PA_0 ~ PH_1

**Example code**

```c
is_pending_EXTI(PB_12); //check the pending bit of PB_12
```



#### clear_pending_EXTI()

clear the pending bit of a specific pin.

```c
void clear_pending_EXTI(PinName_t pinName);
```

**Parameters**

- **pinName**: Port and Pin number, PA_0 ~ PH_1

**Example code**

```c
clear_pending_EXTI(PB_12)	// clear the pending bit of PB_12
```



#### Example code

```c
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecSysTick2.h"
#include "ecEXTI2.h"

#define LED0_PIN   PB_12 		//EVAL board JKIT LED0
#define LED7_PIN   PC_3 		//EVAL board JKIT LED7
#define SW2_PIN    PA_4			//EVAL board JKIT SW2


void led_toggle(PinName_t pinName){
	GPIO_TypeDef *Port;    
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	Port->ODR ^= 1UL << pin;
}

// Initialiization 
void setup(void)
{
		RCC_PLL_init();                 // System Clock = 84MHz
		SysTick_init();                 // SysTick Timer Initialization
		// Initialize GPIOB_12 for Output
		GPIO_init(LED0_PIN, OUTPUT);    // LED0 for EVAL board	
		GPIO_init(LED7_PIN, OUTPUT);    // LED7 for EVAL board
		
		// Initialize GPIOA_4 for Input Button
		GPIO_init(SW2_PIN, INPUT);  // INPUT for EVAL board
		GPIO_pupd(SW2_PIN, PULLUP);  // PULL-UP for EVAL board
		
		// Initialize EXTI PA_4
		EXTI_init(SW2_PIN, FALL, 10);		
}


// MAIN  ----------------------------------------
int main(void) {
	setup();
	while (1){
        GPIO_write(LED7_PIN, HIGH);
        delay_ms(1000);
        GPIO_write(LED7_PIN, LOW);
        delay_ms(1000);
    }
}


void EXTI4_IRQHandler(void) {
	if (is_pending_EXTI(SW2_PIN)) {   
		led_toggle(LED0_PIN);
		clear_pending_EXTI(SW2_PIN);
	}
}
```

### STEPPER MOTOR

#### Header File

`#include "ecStepper2.h"`

```C++
#include "stm32f411xe.h"
#include "ecPinNames.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecSysTick2.h"
			
#ifndef __EC_STEPPER2_H
#define __EC_STEPPER2_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

// Stepper Mode
#define HALF 0
#define FULL 1	 
#define DIR_CW 0
#define DIR_CCW 1	  

// Stepper Motor Spec
// 28BYJ-48 : 64 steps/rev x 1/32 gear = 2048 
#define STEP_PER_REV  (64*32)		

//State number 
typedef enum {
	S0, S1, S2, S3, S4, S5, S6, S7
} StateNum;

// FULL stepping sequence  - FSM
typedef struct {	
  uint32_t next[2];
  uint8_t out[4];
} StateStepper_t;

// Initialization of Stepper Motor
void stepper_init(uint32_t mode, PinName_t *pinStepper);

// Converts Motor [rpm] to step delay in [msec]
void stepper_speed (uint32_t speedRPM);

// Run Stepper Motor for given steps and direction
void stepper_step(uint32_t steps, uint32_t direction);

// Stepper Motor Output for given state
void stepper_out(uint32_t state);

// Stop Stepper Motor
void stepper_stop(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_STEPPER2_H

```



#### stepper\_init()

Initialization of Stepper Motor that includes mode(half, full step) selection and initialization of  4 pins

```c
void stepper_init(uint32_t mode, PinName_t *pinStepper);
```

**Parameters**

* **mode**: HALF(0),  FULL(1) :  full stepping mode, half stepping mode
* **pinStepper**: 4 element array, each element corresponds to 4 pins. (A, B, AN, BN)

**Example code**

```c
stepper_init(HALF, pinStepper); 	
```



#### stepper\_speed()

setting the stepper motor speed in RPM. as

```c
void stepper_speed (uint32_t speedRPM);
```

**Parameters**	

* **speedRPM**: RPM of stepper motor, 1, 2...

**Example code**

```c
stepper_speed(1);		//stepper motor speed 1RPM
```



#### stepper\_step()

Run Stepper Motor for given steps and direction. For each step

Update Present State, Output of Present State, Delay for steppermotor speed is conducted.

```c 
void stepper_step(uint32_t steps, uint32_t direction)
```

**Parameters**

- steps : number of steps, (Motor 28BYJ-48 spec : 2048 per 1 revolution)
- direction : DIR_CW(0), DIR_CCW(1) setting rotation direction. 

**Example code**

``` c 
stepper_step(steps, DIR_CW);  // (Step : 2048, Direction : 0 or 1)
```



#### stepper\_out()

Stepper Motor Output for given state using [GPIO_write()](#gpio_write). 

```c
void stepper_out(uint32_t state)
```

**Parameters**

- state : 0 ~ 3 for full step, 0 ~7 for half step

**Example code**

```c 
stepper_out(state);		
```



#### stepper\_stop()

making stepper motor to stop by setting all the pins LOW. Also reset the counted steps.

``` c  
void stepper_stop(void)
```

**Example code**

```c
stepper_stop();		//stop stepper motor
```



### Example code

```c
#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"
#include "ecStepper2.h"

#define BUTTON_PIN  PC_13


// ( A, B,  AN,  BN)
PinName_t pinStepper[4]    = {PB_10,PB_4,PB_5,PB_3};

// Initialiization 
void setup(void){	
	RCC_PLL_init();                                 // System Clock = 84MHz
	SysTick_init();                                 // Systick init
	
	GPIO_init(BUTTON_PIN, INPUT);           		// GPIOC pin13 initialization
    EXTI_init(BUTTON_PIN, FALL, 0);           		// External Interrupt Setting

	stepper_init(HALF, pinStepper); 				// Stepper GPIO pin initialization
	stepper_speed(1);                          		//  set stepper motor speed
}


int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	uint32_t rev=2;
	uint32_t steps=STEP_PER_REV*rev;
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		stepper_step(steps, DIR_CW);  // (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)
		delay_ms(2000);
		stepper_step(steps, DIR_CCW);  // (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)
		delay_ms(2000);
	}
}



void EXTI15_10_IRQHandler(void) {  
	if (is_pending_EXTI(BUTTON_PIN)) {
		stepper_stop();
		clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
	}
}
```

### UART

#### Header File

`#include "ecUART2.h"`

```C++
#ifndef __EC_USART2_STUDENT_H
#define __EC_USART2_STUDENT_H

#include <stdio.h>
#include <math.h>
#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"


#define POL 		0
#define INT 		1

// You can modify this
#define BAUD_9600	9600
#define BAUD_19200	19200
#define BAUD_38400  38400
#define BAUD_57600	57600
#define BAUD_115200 115200
#define BAUD_921600 921600


/*================ General Configuration ================*/
// General configuration
void USART_init(USART_TypeDef* USARTx, PinName_t pin_GPIO_TX, PinName_t pin_GPIO_RX, uint32_t baud);	// copy of USART_setting
void USART_baud(USART_TypeDef* USARTx, uint32_t baud);
void USART_pins(USART_TypeDef* USARTx, PinName_t pin_GPIO_TX, PinName_t pin_GPIO_RX);

void USART1_baud(uint32_t baud);
void USART2_baud(uint32_t baud);


/*================ PROVIDED  ================*/
/*================ Configuration for each USART ================*/
// Configuration UART 1, 2 using default settings
void USART1_init(void);
void USART2_init(void);

// USART write & read
void USART1_write(uint8_t* buffer, uint32_t nBytes);
void USART2_write(uint8_t* buffer, uint32_t nBytes);
uint8_t USART1_read(void);										
uint8_t USART2_read(void);	

// RX Inturrupt Flag USART1,2
uint32_t is_USART1_RXNE(void);
uint32_t is_USART2_RXNE(void);


/*================ General Configuration ================*/
void USART_clock_enable(USART_TypeDef* USARTx);
void USART_write(USART_TypeDef* USARTx, uint8_t* buffer, uint32_t nBytes);
uint8_t USART_read(USART_TypeDef * USARTx);										
uint32_t is_USART_RXNE(USART_TypeDef * USARTx);
void USART_delay(uint32_t us);  

								

#endif // __EC_USART2_STUDENT_H

```



#### USART\_init()

Initialization of GPIO pin for TX and RX, USARTx (x=2,1,6) configuration

```c
void USART_init(USART_TypeDef* USARTx, PinName_t pin_GPIO_TX, PinName_t pin_GPIO_RX, uint32_t baud);
```

**Parameters**

* **USARTx**: USARTx (x = 2, 1 ,6)
* **pin_GPIO_TX**: PA_9, PA_10  specific Port number
* **pin_GPIO_RX**: PA_2, PA_3  specific Port number
* **baud**: 9600, 19200, 38400 ... 

**Example code**

```c
USART_init(USART2, PA_2, PA_3, 9600) 	
```

#### USART\_baud()

configure Baud-rate

```c
void USART_baud(USART_TypeDef* USARTx, uint32_t baud);
```

**Parameters**

* **USARTx**: USARTx (x = 2, 1, 6)
* **baud**: 9600, 19200, 38400 ... 

**Example code**

```c
USART1_baud(BAUD_9600);  //BAUD = 9600
```


#### USART\_pins()

GPIO pin setup for USARTx TX/RX

```c
void USART_pins(USART_TypeDef* USARTx, PinName_t pin_GPIO_TX, PinName_t pin_GPIO_RX);
```

**Parameters**

* **USARTx**: USARTx (x = 2, 1, 6)
* **pin_GPIO_TX**: PA_9, PA_10  specific Port number
* **pin_GPIO_RX**: PA_2, PA_3  specific Port number

**Example code**

```c
USART_pins(USART1, PA_2, PA_3);
```

#### USART_clock_enable()

Enable USARTx clock (x = 2, 1, 6)

```c
void USART_clock_enable(USART_TypeDef* USARTx);
```

**Parameters**

- **USARTx**: USARTx (x = 2, 1, 6)

**Example code**

```c
USART_clock_enable(USARTx);		//ex) USART_TypeDef *USARTx= USART1
```

#### USART_write()

Wait until TXE (TX empty) bit is set. 

Write the input array element to USART_DR. 

Clear TC bit. 

```c
void USART_write(USART_TypeDef* USARTx, uint8_t* buffer, uint32_t nBytes);
```

**Parameters**

- **USARTx**: USARTx (x = 2, 1, 6)
- **buffer**: address of pointer array
- **nBytes**: array length

**Example code**

```c
USART_write(USART1, PC_string, 7);		//uint8_t PC_string[]="Hi_BT\n\r";
```

#### USART_read()

Wait until RXNE (RX not empty) bit is set by HW.

Read USART_DR

(Reading USART_DR automatically clears the RXNE flag)

```c
uint8_t USART_read(USART_TypeDef * USARTx);
```

**Parameters**

- **USARTx**: USARTx (x = 2, 1, 6)

```c
PC_data = USART_read(USART2);
```

#### is_USART_RXNE()

Read RXNE bit of  USARTx

```c
uint32_t is_USART_RXNE(USART_TypeDef * USARTx);
```

**Parameters**

- **USARTx**: USARTx (x = 2, 1, 6)

```c
if (is_USART_RXNE(USARTx));
```

#### USART_delay()

delay function

```c
void USART_delay(uint32_t us);
```

**Parameters**

- **us**: delay time [usec]

```c
USART_delay(100); 		//100us delay
```

***

### Timer

#### Header File

`#include "ecTIM2.h"`[cite: 1, 2]

```c++
#ifndef __EC_TIM2_H
#define __EC_TIM2_H

#include "stm32f411xe.h"
#include "ecPinNames.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "math.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


//////////////////////////////////////////////
/* Timer Update Interrupt Configuration     */
//////////////////////////////////////////////

// Timer Update Interrupt Initialization
void TIM_UI_init(TIM_TypeDef* TIMx, uint32_t msec);     // 16-bit  msec < 65,530 msec 
void TIM_UI_init_us(TIM_TypeDef* TIMx, uint32_t usec);  // 16-bit  usec < 65,530 usec 

// Timer Update Interrupt On/OFf
void TIM_UI_enable(TIM_TypeDef* TIMx);
void TIM_UI_disable(TIM_TypeDef* TIMx);

// Timer Update Interrupt Flag
uint32_t is_UIF(TIM_TypeDef *TIMx);
void clear_UIF(TIM_TypeDef *TIMx);


////////////////////////////////////////////////////////////////
/* Timer Counter Initialization                              */
////////////////////////////////////////////////////////////////

// Timer Counter Initialization
void TIM_init(TIM_TypeDef *TIMx, uint32_t msec); 
void TIM_init_us(TIM_TypeDef *TIMx, uint32_t usec); 

// Timer Counter Period Config
void TIM_period_ms(TIM_TypeDef* TIMx, uint32_t msec);		
void TIM_period_us(TIM_TypeDef* TIMx, uint32_t usec);  	

// Timer Counter Auxiliary Functions
uint32_t get_TIM_IRQn(TIM_TypeDef* TIMx);
void TIM_clock_enable(TIM_TypeDef* TIMx);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_TIM2_H 
```


#### TIM\_UI\_init()

Initializes the timer counter in milliseconds, enables the Update Interrupt (UIE), and configures the NVIC IRQ with priority 2.

```c
void TIM_UI_init(TIM_TypeDef* TIMx, uint32_t msec);
```

**Parameters**

- **TIMx**: Timer peripheral, `TIM1`\~`TIM5`, `TIM9`\~`TIM11`
- **msec**: Update interrupt period in milliseconds (`1` ~ `6,553` msec for 16-bit ARR at 10 kHz)

**Example code**

```c
TIM_UI_init(TIM2, 1);  // UEV every 1 msec
```



#### TIM\_UI\_init\_us()

Initializes the timer counter in microseconds, enables the Update Interrupt (UIE), and configures the NVIC IRQ with priority 2.

```c
void TIM_UI_init_us(TIM_TypeDef* TIMx, uint32_t usec);
```

**Parameters**

- **TIMx**: Timer peripheral, `TIM1`\~`TIM5`, `TIM9`\~`TIM11`
- **usec**: Update interrupt period in microseconds (`1` ~ `65,530` usec for 16-bit ARR at 1 MHz)

**Example code**

```c
TIM_UI_init_us(TIM2, 1000);  // UEV every 1000 usec = 1 msec
```



#### TIM\_UI\_enable()

Clears any pending update flag and enables the Timer Update Interrupt (`UIE` bit in `DIER`).

```c
void TIM_UI_enable(TIM_TypeDef* TIMx);
```

**Parameters**

- **TIMx**: Timer peripheral, `TIM1`\~`TIM5`, `TIM9`\~`TIM11`

**Example code**

```c
TIM_UI_enable(TIM2);
```



#### TIM\_UI\_disable()

Disables the Timer Update Interrupt (`UIE` bit in `DIER`).

```c
void TIM_UI_disable(TIM_TypeDef* TIMx);
```

**Parameters**

- **TIMx**: Timer peripheral, `TIM1`\~`TIM5`, `TIM9`\~`TIM11`

**Example code**

```c
TIM_UI_disable(TIM2);
```



#### is\_UIF()

Reads and returns the Update Interrupt Flag (`UIF`) status from `TIMx->SR`.

```c
uint32_t is_UIF(TIM_TypeDef *TIMx);
```

**Parameters**

- **TIMx**: Timer peripheral, `TIM1`\~`TIM5`, `TIM9`\~`TIM11`

**Example code**

```c
if (is_UIF(TIM2)) { ... }
```



#### clear\_UIF()

Clears the Update Interrupt Flag (`UIF`) in `TIMx->SR`.

```c
void clear_UIF(TIM_TypeDef *TIMx);
```

**Parameters**

- **TIMx**: Timer peripheral, `TIM1`\~`TIM5`, `TIM9`\~`TIM11`

**Example code**

```c
clear_UIF(TIM2);
```



#### TIM\_init()

Enables the timer clock, configures the counter period in milliseconds (default counter frequency = 10 kHz), sets up-counting mode, and enables the counter.

```c
void TIM_init(TIM_TypeDef *TIMx, uint32_t msec);
```

**Parameters**

- **TIMx**: Timer peripheral, `TIM1`\~`TIM5`, `TIM9`\~`TIM11`
- **msec**: Counter period in milliseconds (`1` ~ `6,553` msec)

**Example code**

```c
TIM_init(TIM2, 500);
```



#### TIM\_init\_us()

Enables the timer clock, configures the counter period in microseconds (default counter frequency = 1 MHz), sets up-counting mode, and enables the counter.

```c
void TIM_init_us(TIM_TypeDef *TIMx, uint32_t usec);
```

**Parameters**

- **TIMx**: Timer peripheral, `TIM1`\~`TIM5`, `TIM9`\~`TIM11`
- **usec**: Counter period in microseconds (`1` ~ `65,530` usec)

**Example code**

```c
TIM_init_us(TIM2, 100);
```



#### TIM\_period\_ms()

Configures the Prescaler (`PSC`) for a 10 kHz counter clock and sets the Auto-Reload Register (`ARR`) for the target period in milliseconds.

```c
void TIM_period_ms(TIM_TypeDef* TIMx, uint32_t msec);
```

**Parameters**

- **TIMx**: Timer peripheral, `TIM1`\~`TIM5`, `TIM9`\~`TIM11`
- **msec**: Target period in milliseconds (`1` ~ `6,553` msec)

**Example code**

```c
TIM_period_ms(TIM2, 10);
```



#### TIM\_period\_us()

Configures the Prescaler (`PSC`) for a 1 MHz counter clock and sets the Auto-Reload Register (`ARR`) for the target period in microseconds.

```c
void TIM_period_us(TIM_TypeDef* TIMx, uint32_t usec);
```

**Parameters**

- **TIMx**: Timer peripheral, `TIM1`\~`TIM5`, `TIM9`\~`TIM11`
- **usec**: Target period in microseconds (`1` ~ `65,530` usec)

**Example code**

```c
TIM_period_us(TIM2, 500);
```



#### TIM\_clock\_enable()

Enables the APB1 or APB2 peripheral clock for the specified timer (`TIM1`\~`TIM5`, `TIM9`\~`TIM11`).

```c
void TIM_clock_enable(TIM_TypeDef* TIMx);
```

**Parameters**

- **TIMx**: Timer peripheral, `TIM1`\~`TIM5`, `TIM9`\~`TIM11`

**Example code**

```c
TIM_clock_enable(TIM2);
```



#### get\_TIM\_IRQn()

Returns the corresponding NVIC IRQ number (`IRQn_Type`) for the specified timer peripheral.

```c
uint32_t get_TIM_IRQn(TIM_TypeDef* TIMx);
```

**Parameters**

- **TIMx**: Timer peripheral, `TIM1`\~`TIM5`, `TIM9`\~`TIM11`

**Example code**

```c
uint32_t IRQn_reg = get_TIM_IRQn(TIM2);
```



#### Example Code

```c
#include "stm32f411xe.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecSysTick2.h"
#include "ecTIM2.h"

#define LD2_PIN PA_5
uint32_t _count = 0;
volatile uint8_t set = 0;

void led_toggle(PinName_t Pin);

// Initialization
void setup(void){
    RCC_PLL_init();
    SysTick_init();
    GPIO_init(LD2_PIN, OUTPUT);

    // TIM2 Update-Event Interrupt every 1 msec
    TIM_UI_init(TIM2, 1);           // UEV every 1 msec
    //TIM_UI_init_us(TIM2, 1000);   // UEV every 1000usec=1msec
}

int main(void) {
    // Initialization --------------------------------------------------
    setup();

    // Infinite Loop ---------------------------------------------------
    while(1){}
}


// TIM2 Update Interrupt Handler
void TIM2_IRQHandler(void){
    if(is_UIF(TIM2)){               // Check UIF(update interrupt flag)
        _count++;
        if (_count > 1000) {
            led_toggle(LD2_PIN);    // Toggle every 1000 msec
            _count = 0;
        }
        clear_UIF(TIM2);            // Clear TIM_UI flag
    }
}

void led_toggle(PinName_t Pin){
    set ^= 1; 
    if(set == 1) GPIO_write(Pin, HIGH);
    else GPIO_write(Pin, LOW);
}
```



### PWM

#### Header File

`#include "ecPWM2.h"`

```c
#ifndef __EC_PWM2_STUDENT_H
#define __EC_PWM2_STUDENT_H

#include "math.h"
#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecTIM2.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/* PWM Output Mode : OCxM field in CCMRx (3 bits) */
#define EC_PWM_MODE1	0	// output active while CNT <  CCR  (default)
#define EC_PWM_MODE2	1	// output active while CNT >= CCR  (inverted)


///////////////////////////////////////////////////
/* 		        EXERCISE					     */
///////////////////////////////////////////////////

// Internal Helper function: for PWM Initialization
void PWM_init_config(PinName_t pinName, uint32_t usec);
// Duty ratio 0~1.0
void PWM_duty(PinName_t pinName, float duty);



///////////////////////////////////////////////////
/* 		GIVEN:  PWM Initialization                */
///////////////////////////////////////////////////

//  Low Frequency PWM initialization in msec. (below 1kHz)
// 	Default: 		50% duty ratio. PWM_mode1, Period in msec.
//  TIM2/TIM5 		(32-bit ARR) : msec 1 ~ 4,294,967
//  TIM1/TIM3/TIM4 	(16-bit ARR) : msec 1 ~ 6,553   
void PWM_init(PinName_t pinName, uint32_t msec);	// 1 to 6,553 msec (16-bit)

//  High-Frequency PWM initialization in usec (1kHz to 100 kHz)
// 	Default: 		50% duty ratio.  PWM_mode1, Period in usec.
//  TIM2/TIM5 		(32-bit ARR) : 	usec 1 ~ 4,294,967
//  TIM1/TIM3/TIM4 	(16-bit ARR) : 	usec 1 ~ 6,553   
void PWM_init_us(PinName_t pinName, uint32_t usec);	// 10 usec and up


///////////////////////////////////////////////////
/* 		GIVEN: DUTY RATIO SETUP                 */
///////////////////////////////////////////////////

// Set Pulse width in msec
void PWM_pulsewidth(PinName_t pinName, uint32_t pulse_width_ms);

// Set Pulse width in usec
void PWM_pulsewidth_us(PinName_t pinName, uint32_t pulse_width_us);


////////////////////////////////////////////////////////////////
/* Internal Helper Functions - GIVEN. DO NOT MODIFY           */
////////////////////////////////////////////////////////////////

// Internal function for PWM output mode : EC_PWM_MODE1 or EC_PWM_MODE2
void PWM_mode_config(TIM_TypeDef *TIMx, int chN, uint32_t mode);
// Internal Helper function for PWM Pin Matching
void PWM_pinmap(PinName_t pinName, TIM_TypeDef **TIMx, int *chN);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_PWM2_STUDENT_H
```

#### PWM_init()

Initializes low-frequency PWM output in milliseconds (default: PWM Mode 1, active high, 50% duty ratio).

```c
void PWM_init(PinName_t pinName, uint32_t msec);
```

**Parameters**

- **pinName**: PWM output pin (`PA_0`\~`PA_1`, `PA_5`\~`PA_6`, `PA_8`\~`PA_10`, `PA_15`, `PB_3`\~`PB_10`, `PC_6`\~`PC_9`)
- **msec**: PWM period in milliseconds (`1` ~ `4,294,967` for 32-bit `TIM2`/`TIM5`; `1` ~ `6,553` for 16-bit `TIM1`/`TIM3`/`TIM4`)

**Example code**



```c
PWM_init(PA_5, 10);  // 10 msec period -> 100 Hz
```

#### PWM_init_us()

Initializes high-frequency PWM output in microseconds (default: PWM Mode 1, active high, 50% duty ratio; minimum `10` usec).

```c
void PWM_init_us(PinName_t pinName, uint32_t usec);
```

**Parameters**

- **pinName**: PWM output pin (`PA_0`\~`PA_1`, `PA_5`\~`PA_6`, `PA_8`\~`PA_10`, `PA_15`, `PB_3`\~`PB_10`, `PC_6`\~`PC_9`)
- **usec**: PWM period in microseconds (`10` ~ `4,294,967` for 32-bit `TIM2`/`TIM5`; `10` ~ `6,553` for 16-bit `TIM1`/`TIM3`/`TIM4`)

**Example code**

```c
PWM_init_us(PA_5, 1000);  // 1 msec period -> 1 kHz
```

#### PWM_duty()

Sets the PWM duty ratio by updating the corresponding channel Capture/Compare Register (`CCRx`).

```c
void PWM_duty(PinName_t pinName, float duty);
```

**Parameters**

- **pinName**: PWM output pin
- **duty**: Duty ratio from `0.0f` to `1.0f` (clamped to `[0.0, 1.0]`)

**Example code**

```c
PWM_duty(PA_5, 0.2f);  // 20% duty ratio
```

#### PWM_pulsewidth()

Sets the PWM active pulse width in milliseconds by converting the duration into a duty ratio.

```c
void PWM_pulsewidth(PinName_t pinName, uint32_t pulse_width_ms);
```

**Parameters**

- **pinName**: PWM output pin
- **pulse_width_ms**: Active pulse width in milliseconds

**Example code**

```c
PWM_pulsewidth(PA_5, 2);  // 2 msec pulse width
```

#### PWM_pulsewidth_us()

Sets the PWM active pulse width in microseconds by converting the duration into a duty ratio.

```c
void PWM_pulsewidth_us(PinName_t pinName, uint32_t pulse_width_us);
```

**Parameters**

- **pinName**: PWM output pin
- **pulse_width_us**: Active pulse width in microseconds

**Example code**

```c
PWM_pulsewidth_us(PA_5, 1500);  // 1500 usec pulse width
```

#### PWM_init_config()

Internal helper function that maps the GPIO pin to its timer/channel, configures Alternate Function (`AF1`~`AF3`), initializes the timer period, configures PWM Mode 1, and enables the timer counter (including `BDTR_MOE` for `TIM1`).

```c
void PWM_init_config(PinName_t pinName, uint32_t usec);
```

**Parameters**

- **pinName**: PWM output pin
- **usec**: PWM period in microseconds

**Example code**

```c
PWM_init_config(PA_5, 10000);
```

#### PWM_mode_config()

Internal helper function that configures the output compare mode (`EC_PWM_MODE1` or `EC_PWM_MODE2`), preload enable (`OCxPE`), default 50% `CCRx` value, active-high polarity, and channel output enable (`CCxE`).

```c
void PWM_mode_config(TIM_TypeDef *TIMx, int chN, uint32_t mode);
```

**Parameters**

- **TIMx**: Timer peripheral (`TIM1`\~`TIM5`, `TIM9`\~`TIM11`)
- **chN**: Timer channel number (`1` ~ `4`)
- **mode**: `EC_PWM_MODE1`(0) or `EC_PWM_MODE2`(1)

**Example code**

```c
PWM_mode_config(TIM2, 1, EC_PWM_MODE1);
```

#### PWM_pinmap()

Internal helper function that maps a `PinName_t` to its corresponding `TIM_TypeDef*` instance and channel number (`1` ~ `4`).

```c
void PWM_pinmap(PinName_t pinName, TIM_TypeDef **TIMx, int *chN);
```

**Parameters**

- **pinName**: PWM output pin
- **TIMx**: Pointer to store the matched timer peripheral
- **chN**: Pointer to store the matched channel number (`1` ~ `4`)

**Example code**

```c
PWM_pinmap(PA_5, &TIMx, &chN);
```

#### Example Code

```c
#include "ecGPIO2.h"
#include "ecSysTick2.h"
#include "ecRCC2.h"
#include "ecTIM2.h"
#include "ecPWM2.h"

// Button Pin & PWM Pin
#define PWM_LED PA_5

// Initialiization 
void setup(void) {  
    RCC_PLL_init();
    SysTick_init();

    // PWM of 10 msec:  TIM2_CH1 (PA_5) 
    PWM_init(PWM_LED, 10);          // 10 msec period -> 100 Hz 
    PWM_duty(PWM_LED, 0.2f);        // 20% of duty
    // PWM_pulsewidth(PWM_LED, 2);  // a Pulse of 2msec =(duty=1/10=20%)

    // PWM of 1 msec:  TIM2_CH1 (PA_5)  
    // PWM_init_us(PWM_LED, 1000);  // 1 msec period -> 1 kHz
    // PWM_duty(PWM_LED, 0.2f);     // 20% of duty  
}

int main(void) {
    // Initialization --------------------------------------------------
    setup();    

    // Infinite Loop ---------------------------------------------------
    while(1){       
        for (int i=0; i<5; i++) {                       
            PWM_duty(PWM_LED, (float)0.2*i);                    
            delay_ms(1000);
        }       
    }
}
```


### Input Capture

#### Header File

`#include "ecICAP2.h"`

```c
#ifndef __EC_ICAP2_H
#define __EC_ICAP2_H

#include "stm32f411xe.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecTIM2.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Input Capture*/


// Edge Type
#define IC_RISE 0
#define IC_FALL 1
#define IC_BOTH 2

// Input Capture Number
#define IC_1 1
#define IC_2 2
#define IC_3 3
#define IC_4 4

// Input Capture Filter 
#define IC_FILTER_0		0		// no filter, transition sampled at fDTS
#define IC_FILTER_1		1		// N = 2 samples at fCK_INT
#define IC_FILTER_2		2		// N = 4 samples at fCK_INT
#define IC_FILTER_3		3		// N = 8 samples at fCK_INT


////////////////////////////////////////////////////////////////
/* Timer Input Capture  Initialization                        */
////////////////////////////////////////////////////////////////

// Default: 1 usec Tick Timer,  Assume TIn=ICn
void ICAP_init(PinName_t pinName, uint32_t edge_type);

// User-Defined IC channel for the pin, 1 usec tick
void ICAP_ICn_init(PinName_t pinName, uint32_t edge_type, uint32_t ICn);

// User-Defined tick in usec.  CALL THIS LAST
// usec range: 1 ~ 780 usec at 84 MHz (PSC is 16-bit).
void ICAP_tick(PinName_t pinName, uint32_t usec);

uint32_t ICAP_read(PinName_t pinName, uint32_t ICn);


//////////////////////////////////////////////
/* Timer Input CC Interrupt Configuration         */
//////////////////////////////////////////////
uint32_t is_CCIF(TIM_TypeDef *TIMx, uint32_t  ICn);  // CCnum= 1~4
void clear_CCIF(TIM_TypeDef *TIMx, uint32_t  ICn);


//////////////////////////////////////////////
/* Internal Functions                       */
//////////////////////////////////////////////
void ICAP_pinmap(PinName_t pinName, TIM_TypeDef **TIMx, int *chN);
void ICAP_filter(TIM_TypeDef *TIMx, uint32_t ICn, uint16_t filterOpt);
void ICAP_ICn_select(TIM_TypeDef *TIMx, uint32_t TIn, uint32_t ICn);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  // __EC_ICAP2_H
~~~

#### ICAP_init()

Initializes Input Capture on the given pin with a default 1 usec timer tick, assuming the Input Capture channel matches the Timer Input channel (`ICn = TIn`).

```c
void ICAP_init(PinName_t pinName, uint32_t edge_type);
```

**Parameters**

- **pinName**: Input capture pin (`PA_0`\~`PA_1`, `PA_5`\~`PA_6`, `PA_8`\~`PA_10`, `PA_15`, `PB_3`\~`PB_10`, `PC_6`\~`PC_9`)
- **edge_type**: `IC_RISE`(0), `IC_FALL`(1), `IC_BOTH`(2)

**Example code**

```c
ICAP_init(PB_6, IC_RISE);
```

#### ICAP_ICn_init()

Initializes a user-defined Input Capture channel (`ICn`) for the given pin with a 1 usec timer tick, AF pin setup, digital filter (`IC_FILTER_3`), trigger edge, and capture/update interrupts.

```c
void ICAP_ICn_init(PinName_t pinName, uint32_t edge_type, uint32_t ICn);
```

**Parameters**

- **pinName**: Input capture pin (`PA_0`\~`PA_1`, `PA_5`\~`PA_6`, `PA_8`\~`PA_10`, `PA_15`, `PB_3`\~`PB_10`, `PC_6`\~`PC_9`)
- **edge_type**: `IC_RISE`(0), `IC_FALL`(1), `IC_BOTH`(2)
- **ICn**: Input Capture channel number, `IC_1`(1) ~ `IC_4`(4)

**Example code**

```c
ICAP_ICn_init(PB_6, IC_FALL, IC_2);
```

#### ICAP_tick()

Configures the timer counter tick duration in microseconds by adjusting the Prescaler (`PSC`) and setting `ARR` to maximum (`0xFFFF` for 16-bit timers, `0xFFFFFFFF` for `TIM2`/`TIM5`). Call this after `ICAP_init()` / `ICAP_ICn_init()`.

```c
void ICAP_tick(PinName_t pinName, uint32_t usec);
```

**Parameters**

- **pinName**: Input capture pin
- **usec**: Timer tick duration in microseconds (`1` ~ `780` usec at 84 MHz)

**Example code**

```c
ICAP_tick(PB_6, 100);  // 1 tick = 100 usec
```

#### ICAP_read()

Reads and returns the captured counter value from `TIMx->CCRn` for the specified Input Capture channel (`ICn`).

```c
uint32_t ICAP_read(PinName_t pinName, uint32_t ICn);
```

**Parameters**

- **pinName**: Input capture pin
- **ICn**: Input Capture channel number, `IC_1`(1) ~ `IC_4`(4)

**Example code**

```c
cap_prev = ICAP_read(PB_6, IC_1);
```

#### is_CCIF()

Checks and returns the Capture/Compare Interrupt Flag (`CCnIF`) status in `TIMx->SR` for channel `ICn`.

```c
uint32_t is_CCIF(TIM_TypeDef *TIMx, uint32_t ICn);
```

**Parameters**

- **TIMx**: Timer peripheral (`TIM1`\~`TIM5`, `TIM9`\~`TIM11`)
- **ICn**: Input Capture channel number, `IC_1`(1) ~ `IC_4`(4)

**Example code**

```c
if (is_CCIF(TIM4, IC_1)) { ... }
```

#### clear_CCIF()

Clears the Capture/Compare Interrupt Flag (`CCnIF`) in `TIMx->SR` for channel `ICn`.

```c
void clear_CCIF(TIM_TypeDef *TIMx, uint32_t ICn);
```

**Parameters**

- **TIMx**: Timer peripheral (`TIM1`\~`TIM5`, `TIM9`\~`TIM11`)
- **ICn**: Input Capture channel number, `IC_1`(1) ~ `IC_4`(4)

**Example code**

```c
clear_CCIF(TIM4, IC_1);
```

#### ICAP_pinmap()

Internal helper function that maps a `PinName_t` to its corresponding `TIM_TypeDef*` peripheral and timer channel number (`1` ~ `4`).

```c
void ICAP_pinmap(PinName_t pinName, TIM_TypeDef **TIMx, int *chN);
```

**Parameters**

- **pinName**: Input capture pin
- **TIMx**: Pointer to store the matched timer peripheral
- **chN**: Pointer to store the matched channel number (`1` ~ `4`)

**Example code**

```c
ICAP_pinmap(PB_6, &TIMx, &TIn);
```

#### ICAP_filter()

Internal helper function that sets the input capture filter duration (`ICnF` bits in `CCMR1`/`CCMR2`) for channel `ICn`.

```c
void ICAP_filter(TIM_TypeDef *TIMx, uint32_t ICn, uint16_t filterOpt);
```

**Parameters**

- **TIMx**: Timer peripheral (`TIM1`\~`TIM5`, `TIM9`\~`TIM11`)
- **ICn**: Input Capture channel number, `IC_1`(1) ~ `IC_4`(4)
- **filterOpt**: `IC_FILTER_0`(0) ~ `IC_FILTER_3`(3)

**Example code**

```c
ICAP_filter(TIM4, IC_1, IC_FILTER_3);
```

#### ICAP_ICn_select()

Internal helper function that maps Timer Input (`TIn`) to Input Capture channel (`ICn`) by configuring the `CCnS` bits in `CCMR1`/`CCMR2`.

```c
void ICAP_ICn_select(TIM_TypeDef *TIMx, uint32_t TIn, uint32_t ICn);
```

**Parameters**

- **TIMx**: Timer peripheral (`TIM1`\~`TIM5`, `TIM9`\~`TIM11`)
- **TIn**: Timer input channel (`1` ~ `4`)
- **ICn**: Input Capture channel number, `IC_1`(1) ~ `IC_4`(4)

**Example code**

```c
ICAP_ICn_select(TIM4, 1, IC_2);
```

#### Example Code

```c
#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecSysTick2.h"
#include "ecTIM2.h"
#include "ecICAP2.h"
#include "ecPWM2.h"
#include "ecUART2.h"

#define ICAP_PIN    PB_6        // TIM4_CH1 : capture input
#define PWM_PIN     PA_6        // TIM3_CH1 : test signal (jumper PA_6 -> PB_6)
#define LED_PIN     PA_5

uint32_t pwm_period_ms = 1000;
uint32_t uTick = 100;
uint32_t timer_arr = 65536;     // ticks per counter wrap (ARR+1)

volatile uint32_t ovf_cnt = 0;      // counts overflows
volatile uint32_t cap_prev = 0;     // CCR of the previous rising edge
volatile uint32_t cap_curr = 0;     // CCR of the current falling edge
volatile uint32_t counts = 0;       // [pulses]
volatile float timeInterval = 0;    // [usec]
volatile uint8_t set = 0;

void led_toggle(PinName_t Pin);

void setup(void){
    RCC_PLL_init();
    SysTick_init();
    GPIO_init(LED_PIN, OUTPUT);
    USART_init(USART2, PA_2, PA_3, 9600);

    // PWM: Test signal of period_ms of 50% duty 
    PWM_init(PWM_PIN, pwm_period_ms);
    PWM_duty(PWM_PIN, 0.5f);

    // Input capture rising edge TIn=ICn, tick = uTick usec    
    ICAP_init(ICAP_PIN, IC_RISE);
    ICAP_ICn_init(ICAP_PIN, IC_FALL, IC_2);     // TI1 -> IC2, falling
    ICAP_tick(ICAP_PIN, uTick);         

    timer_arr = TIM4->ARR + 1;
}

int main(void){
    setup();
    printf("TU_TIM_ICAP : jumper PA_6 -> PB_6, Between RISE/FALL Edge, expect %lu msec\r\n", pwm_period_ms/2);

    while(1){
        printf("counts %lu, timeInterval = (%.2f msec)\r\n", counts, timeInterval/1000);        
        led_toggle(LED_PIN);
        delay_ms(1000);
    }
}

void TIM4_IRQHandler(void){
    // Counter overflow 
    if(is_UIF(TIM4)){
        ovf_cnt++;
        clear_UIF(TIM4);
    }

    // Rising edge captured on IC1
    if(is_CCIF(TIM4, IC_1)){                    // IC1 : rising edge, SAME pin (TI1)
        cap_prev = ICAP_read(ICAP_PIN, IC_1);
        clear_CCIF(TIM4, IC_1);                                
    }

    // Falling edge captured on IC2
    if(is_CCIF(TIM4, IC_2)){                    // IC2 : falling edge, SAME pin (TI1)       
        cap_curr = ICAP_read(ICAP_PIN, IC_2);

        // Ticks between the two edges, then scaled to usec.        
        counts = (cap_curr - cap_prev) + (ovf_cnt * timer_arr);
        timeInterval = counts * uTick;

        ovf_cnt = 0; 
        clear_CCIF(TIM4, IC_2);
    }   
}

void led_toggle(PinName_t Pin){
    set ^= 1; 
    if(set == 1) GPIO_write(Pin, HIGH);
    else GPIO_write(Pin, LOW);
}
```
