# EC-STM32F4-22200326

### Embedded Controller - STM32F411 Driver Library

Written by: Jihoon Park

Program: C/C++

IDE/Compiler: Keil uVision 5

OS: WIn10/11

MCU: STM32F411RE, Nucleo-64

**Table of Contents**

* [GPIO Digital In/Out](#gpio digital inout)
  * [Header File](/ec/ec-course/tutorial.md#header-file)
  * [GPIO\_init()](/ec/ec-course/tutorial.md#gpio-init----)
  * [GPIO\_mode()](/ec/ec-course/tutorial.md#gpio-mode----)
  * [GPIO\_write()](/ec/ec-course/tutorial.md#gpio-write----)
  * [GPIO\_read()](/ec/ec-course/tutorial.md#gpio-read----)
  * [GPIO\_ospeed()](/ec/ec-course/tutorial.md#gpio-ospeed----)
  * [GPIO\_otype()](/ec/ec-course/tutorial.md#gpio-otype----)
  * [GPIO\_pupdr()](/ec/ec-course/tutorial.md#gpio-pupdr----)
  * [Example Code](/ec/ec-course/tutorial.md)
* [EXTI](/ec/ec-course/tutorial.md#gpio-digital-inout)
  * [Header File](/ec/ec-course/tutorial.md#header-file)
  * EXTI_init()
  * EXTI_enable
  * EXTI_disable
  * is_pending_EXTI
  * clear_pending_EXTI

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

