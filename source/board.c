#include "board.h"
#include "stm32f30x.h"                  // Device header

void led_init(void){
	//Turn on the GPIOB peripherial
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	//Configure PB13  as push pull ouput an set the output to high
	GPIOB->MODER &=~(GPIO_MODER_MODER13);
	GPIOB->MODER |=GPIO_MODER_MODER13_0;//output
	GPIOB->ODR |= GPIO_ODR_13;
}

void led_setState(int led_state){
	if(led_state == LED_STATE_ON){
		GPIOB->BSRR = GPIO_BSRR_BS_13;
	}else{
		GPIOB->BSRR = GPIO_BSRR_BR_13;
	}
}
