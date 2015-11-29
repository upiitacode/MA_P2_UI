#include "MainApp.h"
#include "cmsis_os.h"

void MainApp::main(SerialStream* serial){
	while(1){
		serial->printf("Thread: main, Valve on\n");
		osDelay(10);
		serial->printf("Thread: main, Valve off\n");
		osDelay(10);
	}
}
