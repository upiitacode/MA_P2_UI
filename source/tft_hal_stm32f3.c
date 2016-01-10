#include "tft_hal.h"
#include "stm32f30x.h"                  // Device header


/**
 * CS PB0
 * RS PB1
 * WR PB2
 * RD PB3
 * RST PB4
 * DP PC[0-15]
 */

void TFT_HAL_init(){
	//Turn on the GPIOB peripherial
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	//Configure PB[0..4] as push pull ouput an set the output to high
	GPIOB->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 |
		GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER4);
	GPIOB->MODER |= (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 |
		GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0);
	//Turn on the GPIOC peripherial
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	//GPIOC[0..15] as output
	GPIOC->MODER = (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 |
		GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 |
		GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 |
		GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 |
		GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 |
		GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 |
		GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 |
		GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
}

void TFT_HAL_DP(uint16_t data){
	GPIOC->ODR = data;
}

void TFT_HAL_CS(unsigned char data){
	if(data == 0){
		GPIOB->BSRR = GPIO_BSRR_BR_0;
	}else{
		GPIOB->BSRR = GPIO_BSRR_BS_0;
	}
}

void TFT_HAL_RS(unsigned char data){
	if(data == 0){
		GPIOB->BSRR = GPIO_BSRR_BR_1;
	}else{
		GPIOB->BSRR = GPIO_BSRR_BS_1;
	}
}

void TFT_HAL_WR(unsigned char data){
	if(data == 0){
		GPIOB->BSRR = GPIO_BSRR_BR_2;
	}else{
		GPIOB->BSRR = GPIO_BSRR_BS_2;
	}
}

void TFT_HAL_RD(unsigned char data){
	if(data == 0){
		GPIOB->BSRR = GPIO_BSRR_BR_3;
	}else{
		GPIOB->BSRR = GPIO_BSRR_BS_3;
	}
}

void TFT_HAL_RST(unsigned char data){
	if(data == 0){
		GPIOB->BSRR = GPIO_BSRR_BR_4;
	}else{
		GPIOB->BSRR = GPIO_BSRR_BS_4;
	}
}
