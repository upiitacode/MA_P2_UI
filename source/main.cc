#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "SerialStream_stm32f3.h"
#include "stm32f30x.h"                  // Device header

void tarea1(void const * arguments); //tarea 1
osThreadId  tarea1ID;	//identificador del hilo tarea 1
osThreadDef (tarea1,osPriorityNormal,1,0);// macro para definir tareas (aputandor de la funcion, prioridad,?,?)

void tarea2(void const * arguments); //tarea 2
osThreadId  tarea2ID;	//identificador del hilo  tarea 2
osThreadDef (tarea2,osPriorityNormal,1,0);// macro para definir tareas (aputandor de la funcion, prioridad,?,?)

void tarea1Init(void);//funcion que iniciliza la tarea1
void tarea2Init(void);//funcion que iniciliza la tarea1

void osInitiAll(void);

void led_init(void);
void button_init(void);
void waitButtonPress(void);

SerialUSART2* serial;
#define SIGNAL_BUTTON 0x1
osThreadId button_thread_id;

int main(){
	//Hardware initialization
	serial = new SerialUSART2(9600);
	button_init();
	//Operating System initialization
	osInitiAll();
	serial->printf("\nSystem ready\n");
	//User application
	while(1){
		waitButtonPress();
		serial->printf("Valve on\n");
		osDelay(1000);
		serial->printf("Valve off\n");
	}
}

void osInitiAll(void){
	osKernelInitialize();
	tarea1Init();
	tarea2Init();
	osKernelStart();
}

void tarea1Init(void){
	tarea1ID= osThreadCreate(osThread(tarea1),NULL);
}

void tarea2Init(void){
	tarea2ID= osThreadCreate(osThread(tarea2),NULL);
}

void tarea1(void const * arguments){
	while(1){
		osDelay(1000);
	}
}

void tarea2(void const * arguments){
	while(1){
		osDelay(1000);
	}
}

void led_init(void){
	//Turn on the GPIOB peripherial
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	//Configure PB13  as push pull ouput an set the output to high
	GPIOB->MODER &=~(GPIO_MODER_MODER13);
	GPIOB->MODER |=GPIO_MODER_MODER13_0;//output
	GPIOB->ODR |= GPIO_ODR_13;
}

void button_init(void){
	//needed for interrupt source remaping
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

	//Configure PA13 as input with pull-up
	GPIOC->MODER &=~(GPIO_MODER_MODER13);
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR13_0;

	//configure interrupt
	RCC->APB2ENR|= RCC_APB2ENR_SYSCFGEN;//Enable sysconfig registers
	SYSCFG->EXTICR[3] |=SYSCFG_EXTICR4_EXTI13_PC;
	EXTI->IMR |= EXTI_IMR_MR13;
	EXTI->FTSR |= EXTI_FTSR_TR13;
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void waitButtonPress(void){
	button_thread_id = osThreadGetId();
	osSignalClear(button_thread_id, SIGNAL_BUTTON);
	osSignalWait(SIGNAL_BUTTON,osWaitForever);
}

/**
 * Exteral interrupt handler
 */
extern "C"
{
	void EXTI15_10_IRQHandler(void){
		EXTI->PR = EXTI_PR_PR13;
		osSignalSet(button_thread_id, SIGNAL_BUTTON);
	}
}
