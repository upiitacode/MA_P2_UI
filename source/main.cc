#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "SyncSerial_stm32f3.h"
#include "MainApp.h"
#include "safe_stdlib.h"
#include "board.h"
#include "tft_driver.h"
#include <math.h>

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

void TFT_Plot(unsigned short x, unsigned short xlen, unsigned short y, unsigned short ylen, const int* pData, int length){
	TFT_Box(x,y-ylen,x+xlen,y,Black);
	TFT_H_Line(x,x+xlen,y,White);
	TFT_V_Line(y-ylen,y,x,White);
	for(int i = 0; i < length; i++){
		TFT_Dot(x+i+1,y-pData[i]-1,Yellow);
	}
}

int get_sine(void){
	static int i = 0;
	return(sin(i++*0.05*2*3.1416)*0.5+0.5)*48;
	
}
#define SCOPE_BUFFER_SIZE 128
#define SCOPE_POS_X 10
#define SCOPE_POS_Y 80
int scope_buffer[SCOPE_BUFFER_SIZE];
int scope_buffer_index = 0;
void ScopeInit(){
	TFT_Plot(SCOPE_POS_X,150,SCOPE_POS_Y,50,scope_buffer,SCOPE_BUFFER_SIZE);
}

void Scope_WriteLine(int index, unsigned short color){
	unsigned short x1,x2,y1,y2;
	x1 = SCOPE_POS_X+index+1;
	x2 = SCOPE_POS_X+index+2;
	y1 = SCOPE_POS_Y-scope_buffer[index]-1;
	y2 = SCOPE_POS_Y-scope_buffer[index+1]-1;
	if(y1 < y2){
		TFT_Line(x1,y1,x2,y2,color);
	}else{
		TFT_Line(x2,y2,x1,y1,color);
	}
}


void ScopeUpdate(int Datos){
	if(scope_buffer_index  > 0){
		Scope_WriteLine(scope_buffer_index-1, Black);
	}
	if(scope_buffer_index < (SCOPE_BUFFER_SIZE -1)){
		Scope_WriteLine(scope_buffer_index, Black);
	}
	
	scope_buffer[scope_buffer_index] = Datos;
	
	if(scope_buffer_index  > 1){
		Scope_WriteLine(scope_buffer_index-2, Yellow);
	}
	if(scope_buffer_index  > 0){
		Scope_WriteLine(scope_buffer_index-1, Yellow);
	}
	if(scope_buffer_index < (SCOPE_BUFFER_SIZE -1)){
		Scope_WriteLine(scope_buffer_index, Yellow);
	}
	scope_buffer_index++;	
	scope_buffer_index %= SCOPE_BUFFER_SIZE;
}

void tarea1(void const * arguments){
	TFT_Fill(Blue);	
	TFT_Text("Hello, World!",10,10,8,Yellow,Blue);
	ScopeInit();
	while(1){
		ScopeUpdate(get_sine());
		osDelay(5);
	}
}
