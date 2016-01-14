#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "SyncSerial_stm32f3.h"
#include "MainApp.h"
#include "safe_stdlib.h"
#include "board.h"
#include "tft_driver.h"
#include "os_serial_stdio.h"
#include "os_usart_stm32f0.h"
#include "cadc_stm32f3.h"
#include "ctimers_stm32f3.h"
#include <math.h>

void tarea1(void const * arguments); //tarea 1
osThreadId  tarea1ID;	//identificador del hilo tarea 1
osThreadDef (tarea1,osPriorityNormal,1,0);// macro para definir tareas (aputandor de la funcion, prioridad,?,?)

void tarea1Init(void);//funcion que iniciliza la tarea1

void tarea2(void const * arguments); //tarea 1
osThreadId  tarea2ID;	//identificador del hilo tarea 1
osThreadDef (tarea2,osPriorityNormal,1,0);// macro para definir tareas (aputandor de la funcion, prioridad,?,?)

void tarea3(void const * arguments); //tarea 1
osThreadId  tarea3ID;	//identificador del hilo tarea 1
osThreadDef (tarea3,osPriorityNormal,1,0);// macro para definir tareas (aputandor de la funcion, prioridad,?,?)

void tarea1Init(void);//funcion que iniciliza la tarea1
void tarea2Init(void);//funcion que iniciliza la tarea1
void tarea3Init(void);//funcion que iniciliza la tarea1

void osInitiAll(void);

SerialStream* serial;

char inputBuffer[80];


void adc_timer6_init(void){
	timer6_init(10000, PERIOD_IN_MICROSECONDS);
	adc_injected(ADC_TRIGGER_TIMER6);
}

void adc_timer6_start(void){
	timer6_start();
}

volatile int duty_cycle = 0;

int main(){
	//Kernel initialization
	osKernelInitialize();
	//Hardware initialization
	os_serial_init();
	os_usart1_init(9600);
	serial = new SyncSerialUSART2(9600);
	led_init();
	adc_timer6_init();
	TFT_Init();
	//Operating System initialization
	osInitiAll();
	//Start Thread switching
	osKernelStart();
	//User application
	adc_timer6_start();
	serial->printf("\nSystem ready\n");
	int adc_reading;
	while(1){
		adc_reading = adc_getInjectedChannelValue(ADC_INJECTED_CH1);
		duty_cycle = (int)(((float)adc_reading)*(100.0/4095.0));
		serial->printf("D%d\n",duty_cycle);
		osDelay(200);
	}
}

void osInitiAll(void){
	tarea1Init();
	tarea2Init();
	tarea3Init();
}

void tarea1Init(void){
	tarea1ID= osThreadCreate(osThread(tarea1),NULL);
}


void tarea2Init(void){
	tarea2ID= osThreadCreate(osThread(tarea2),NULL);
}

void tarea3Init(void){
	tarea3ID= osThreadCreate(osThread(tarea3),NULL);
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
#define SCOPE_POS_Y 90
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

volatile int motor_rpm;

#define TEMP_BUFFER_SIZE 20
void encoder_update(int rpm){
	static int last_rpm = 0;
	char tempBuffer[TEMP_BUFFER_SIZE];
	snprintf(tempBuffer,TEMP_BUFFER_SIZE,"%4d RPM",last_rpm);
	TFT_Text(tempBuffer,170,85,8,Blue,Blue);
	snprintf(tempBuffer,TEMP_BUFFER_SIZE,"%4d RPM",rpm);
	TFT_Text(tempBuffer,170,85,8,Yellow,Blue);
	last_rpm = rpm;
}

void dc_update(int dc){
	static int last_dc = 0;
	char tempBuffer[TEMP_BUFFER_SIZE];
	snprintf(tempBuffer,TEMP_BUFFER_SIZE,"%3d%%",last_dc);
	TFT_Text(tempBuffer,170,60,8,Blue,Blue);
	snprintf(tempBuffer,TEMP_BUFFER_SIZE,"%3d%%",dc);
	TFT_Text(tempBuffer,170,60,8,Yellow,Blue);
	last_dc = dc;
}

void tarea1(void const * arguments){
	TFT_Fill(Blue);
	TFT_Text("UPIITA: Micros Avanazados",10,10,8,Yellow,Blue);
	TFT_Text("Grafica encoder",10,20,8,Yellow,Blue);
	TFT_Text("DC:",170,50,8,Yellow,Blue);
	TFT_Text("Encoder:",170,75,8,Yellow,Blue);
	ScopeInit();
	while(1){
		ScopeUpdate(motor_rpm/100);
		dc_update(duty_cycle);
		encoder_update(motor_rpm);
		osDelay(20);
	}
}

void tarea2(void const * arguments){
	int received_integer = 0;
	while(1){
		os_usart1_gets(inputBuffer);
		if(inputBuffer[0] == 'R'){
			if(sscanf((inputBuffer+1),"%d",&received_integer)){
				motor_rpm = received_integer;
				serial->printf("R%d\n",motor_rpm);
			}
		}
		osThreadYield();
	}
}

void tarea3(void const * arguments){
	while(1){
		osDelay(1000);
	}
}
