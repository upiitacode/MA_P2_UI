#include "SyncSerial_stm32f3.h"
#include "retarget_stm32f3.h"
#include "cmsis_os.h"
#include "safe_stdlib.h"

osMutexDef (usart2_tx_mutex);
osMutexId usart2_tx_mutex_id;

SyncSerialUSART2::SyncSerialUSART2(int baudrate){
	usart2_tx_mutex_id = osMutexCreate(osMutex(usart2_tx_mutex));
	USART2_init(baudrate);
}

void SyncSerialUSART2::sendChar(char ch){
	osMutexWait(usart2_tx_mutex_id, osWaitForever);
	USART2_sendChar(ch);
	osMutexRelease(usart2_tx_mutex_id);
}

char SyncSerialUSART2::getChar(void){
	return USART2_getChar();
}

void SyncSerialUSART2::puts(const char * pString){
	osMutexWait(usart2_tx_mutex_id, osWaitForever);
	SerialStream::puts(pString);
	osMutexRelease(usart2_tx_mutex_id);
}

void SyncSerialUSART2::printf(const char * format ,...){
	char * tempBuffer;
	int bufferSize;

	va_list args;
	va_start(args, format);

	bufferSize = vsnprintf(NULL, 0,format, args);
	bufferSize++;
	tempBuffer = (char*) safe_malloc(bufferSize);
	vsnprintf(tempBuffer,bufferSize,format,args);

	va_end(args);

	this->puts(tempBuffer);
	safe_free(tempBuffer);
}
