#ifndef _SYNCSERIAL_STM32F3_H
#define _SYNCSERIAL_STM32F3_H

#include "SerialStream.h"

class SyncSerialUSART2: public SerialStream{
	public:
		SyncSerialUSART2(int baudrate);
		virtual char getChar(void);
		virtual void sendChar(char c);
		virtual void puts(const char * pString);
		virtual void printf(const char * format, ...) __attribute__ ((format (printf, 2, 3)));
};

#endif// _SYNCSERIAL_STM32F3_H
