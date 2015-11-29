#ifndef _SERIALSTREAM_H
#define _SERIALSTREAM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

class SerialStream{
	public:
		virtual char getChar(void) = 0;
		virtual void sendChar(char) = 0;
		virtual void puts(const char * pString);
		virtual int gets(char * pBuffer, int bufferSize);
		virtual void printf(const char * format, ...) __attribute__ ((format (printf, 2, 3)));
};

#endif// _SERIALSTREAM_H
