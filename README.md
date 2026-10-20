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
* [Stepper](#stepper-mot0r)
  * [Header File](#header-file-2)
  * [stepper_init()](#stepper_init)
  * [stepper_speed()](#stepper_speed)
  * [stepper_step()](#stepper_step)
  * [stepper_out()](#stepper_out)
  * [stepper_stop()](#stepper_stop)

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



