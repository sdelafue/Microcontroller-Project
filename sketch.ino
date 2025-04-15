#include "stm32c0xx.h"
#include "stdint.h"

#define LED_PIN0 7    // Pin for LED
#define LED_PIN1 8    // Pin for LED
#define LED_PIN2 9    // Pin for LED
#define LED_PIN3 10   // Pin for LED
#define LED_PIN4 11   // Pin for LED
#define LED_PIN5 12   // Pin for LED
#define LED_PIN6 13   // Pin for LED
#define LED_PIN7 14   // Pin for LED
#define LED_PIN8 15   // Pin for LED

#define ROW_OUT0 0    // Pin for matrix row 0
#define ROW_OUT1 1    // Pin for matrix row 1
#define ROW_OUT2 2    // Pin for matrix row 2

#define COL_IN0 4     // Pin for matrix column 0
#define COL_IN1 5     // Pin for matrix column 1
#define COL_IN2 6     // Pin for matrix column 2

void GPIO_Init(void);   //GPIO initializer
void delay_ms(uint32_t ms); //delay function in ms

// array of LED pins for easier accessing
const uint32_t ledPins[] = {
  LED_PIN0, //[0]
  LED_PIN1,
  LED_PIN2,
  LED_PIN3,
  LED_PIN4,
  LED_PIN5,
  LED_PIN6,
  LED_PIN7,
  LED_PIN8  //[8]
};

const uint32_t rowPins[] = {
  ROW_OUT0, //[0]
  ROW_OUT1,
  ROW_OUT2  //[2]
};

const uint32_t colPins[] = {
  COL_IN0, //[0]
  COL_IN1,
  COL_IN2  //[2]
};


// variable holding the amount of led pins used
int numLEDs = sizeof(ledPins) / sizeof(ledPins[0]);


int main(void) {
  //initialize the GPIO pins
  GPIO_Init();

//this code was just to make sure that all the gpios worked correctly
  for(int i=0; i <=2; i++) {
      GPIOA->ODR |= (1 << rowPins[i]);}
      //GPIOA->ODR |=  (1 << ROW_OUT1);
  while (1) {
    
    while ( (GPIOA->IDR) & (1 << COL_IN0)
      || (GPIOA->IDR) & (1 << COL_IN1)
      || (GPIOA->IDR) & (1 << COL_IN2) ) {
      // Button is pressed (logic high)
      GPIOA->ODR &= ~(1 << LED_PIN0);  // Turn off LED
      GPIOA->ODR |=  (1 << LED_PIN1); //turn on led
      GPIOA->ODR &= ~(1 << LED_PIN2);  // Turn off LED
      GPIOA->ODR |=  (1 << LED_PIN3); //turn on led
      GPIOA->ODR &= ~(1 << LED_PIN4);  // Turn off LED
      GPIOA->ODR |=  (1 << LED_PIN5); //turn on led
      GPIOA->ODR &= ~(1 << LED_PIN6);  // Turn off LED
      GPIOA->ODR |=  (1 << LED_PIN7); //turn on led
      GPIOA->ODR &= ~(1 << LED_PIN8);  // Turn off LED
    } 
      GPIOA->ODR |=  (1 << LED_PIN0); //turn on led
      GPIOA->ODR &= ~(1 << LED_PIN1);  // Turn off LED
      GPIOA->ODR |=  (1 << LED_PIN2); //turn on led
      GPIOA->ODR &= ~(1 << LED_PIN3);  // Turn off LED
      GPIOA->ODR |=  (1 << LED_PIN4); //turn on led
      GPIOA->ODR &= ~(1 << LED_PIN5);  // Turn off LED
      GPIOA->ODR |=  (1 << LED_PIN6); //turn on led
      GPIOA->ODR &= ~(1 << LED_PIN7);  // Turn off LED
      GPIOA->ODR |=  (1 << LED_PIN8); //turn on led
    
  }
  return 0;
}

void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 500; i++);
}


//works for input:
//PA0,1,(2 BUT DEBUG),4,5,6,7,8,9
//PA0 output works with PA456789 inputs
//PA1 output works with PA4567 inputs
//PA2 output works with PA567 inputs

//so inputs will be PA456

//real
//Works for output:
//PA1,2,3,(0 BUTNOTWITH PA3 AS IN)

//NOTE: PA0 AS OUTPUT AND PA3 AS INPUT COMBO DOESN'T WORK. IT DOES NOT OUTPUT A SIGNAL.
//reserved PAs: 012 456
//led outputs? PA: 3   7



void GPIO_Init(void) {
  // 1. Enable clock for GPIOA
  RCC->IOPENR |= (1 << 0);  // Turn on clock for GPIOA

  //configure matrix row pins as outputs
  for(int i = 0; i <=2; i++) {
    GPIOA->MODER &= ~(3 << (rowPins[i] * 2));  // Clear mode bits
    GPIOA->MODER |=  (1 << (rowPins[i] * 2));  // Set row pins as output (01)
    GPIOA->OTYPER &= ~(1 << (rowPins[i])); //Push-pull output (leave as is)
    GPIOA->OSPEEDR &= ~(3 << (rowPins[i] *2)); //clears speed
    GPIOA->OSPEEDR |= (3 << (rowPins[i] *2));  //Sets speed
    GPIOA->PUPDR &= ~(3 << (rowPins[i] *2)); //Clears Pull-up / Pull-down
  }

  //configure column pins as inputs
  for(int i = 0; i <=2; i++) {
    GPIOA->MODER &= ~(3 << (colPins[i] * 2));  // Clear mode bits
    GPIOA->MODER |=  (0 << (colPins[i] * 2));  // Set column pins as inputs
    GPIOA->OTYPER &= ~(1 << (colPins[i])); //Push-pull output (leave as is)
    GPIOA->OSPEEDR &= ~(3 << (colPins[i] *2)); //clears speed
    GPIOA->OSPEEDR |= (3 << (colPins[i] *2));  //Sets speed
    GPIOA->PUPDR &= ~(3 << (colPins[i] *2)); //Clears Pull-up / Pull-down
    GPIOA->PUPDR |= (2 << (colPins[i] *2)); //Enable Pull-down
  }

  //configure led pins as outputs
  for(int i = 0; i <=numLEDs; i++) {
    GPIOA->MODER &= ~(3 << (ledPins[i] * 2));  // Clear mode bits for PA2
    GPIOA->MODER |=  (1 << (ledPins[i] * 2));  // Set PA2 as output (01)
    GPIOA->OTYPER &= ~(1 << (ledPins[i])); //Push-pull output (leave as is)
    GPIOA->OSPEEDR &= ~(3 << (ledPins[i] *2)); //clears speed
    GPIOA->OSPEEDR |= (3 << (ledPins[i] *2));  //Sets speed
    GPIOA->PUPDR &= ~(3 << (ledPins[i] *2)); //Clears Pull-up / Pull-down
  }

  //RCC->IOPENR |= (1 << 1); //Enable GPIOB clock
  //Configure PBX-PBY for the 4-digit 7 segment display
  // for (int i = X; i <=Y; i++) {
  //   GPIOA->MODER &= ~(3 << (i * 2));  //Clear MODER bits
  //   GPIOA->MODER |= (1 << (i * 2));  //Set mode to 1 (output)
  //   GPIOA->OTYPER &= ~(1 << i); //Push-pull output (leave as is)
  //   GPIOA->OSPEEDR &= ~(3 << (i *2)); //clears speed
  //   GPIOA->OSPEEDR |= (1 << (i *2));  //Sets speed
  //   GPIOA->PUPDR &= ~(3 << (i *2)); //Pull-up / Pull-down ???
  // }

}
