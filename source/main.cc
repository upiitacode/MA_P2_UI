#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "SyncSerial_stm32f3.h"
#include "MainApp.h"
#include "safe_stdlib.h"
#include "board.h"
#include "tft_driver.h"

void tarea1(void const * arguments); //tarea 1
osThreadId  tarea1ID;	//identificador del hilo tarea 1
osThreadDef (tarea1,osPriorityNormal,1,0);// macro para definir tareas (aputandor de la funcion, prioridad,?,?)


void tarea1Init(void);//funcion que iniciliza la tarea1

void osInitiAll(void);

SerialStream* serial;

int main(){
	osKernelInitialize();
	//Hardware initialization
	serial = new SyncSerialUSART2(9600);
	led_init();
	TFT_Init();
	//Operating System initialization
	osInitiAll();
	serial->printf("\nSystem ready\n");
	//User application
	MainApp::main(serial);
}

void osInitiAll(void){
	safe_init();
	tarea1Init();
	osKernelStart();
}

void tarea1Init(void){
	tarea1ID= osThreadCreate(osThread(tarea1),NULL);
}

void tarea1(void const * arguments){
	TFT_Fill(Black);
	while(1){
		TFT_Fill(Black);
		TFT_Text("Hello, World!",10,10,8,Green,Black);
		osDelay(1000);
	}
}
