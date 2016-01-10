#include "MainApp.h"
#include "cmsis_os.h"

void MainApp::main(SerialStream* serial){
	int count = 0;
	while(1){
		serial->printf("Count = %d\n", count);
		osDelay(1000);
		count++;
	}
}
