#ifndef _CADC_STM32F3_H
#define _CADC_STM32F3_H

#define ADC_TRIGGER_NONE 0
#define ADC_TRIGGER_TIMER2 1
#define ADC_TRIGGER_TIMER6 2
#define ADC_TRIGGER_TIMER15 3
#define ADC_TRIGGER_TIMER16 4

#define DONT_USE_TRIGGER 0
#define USE_TRIGGER 1

#define ADC_INJECTED_CH1 0
#define ADC_INJECTED_CH2 1
#define ADC_INJECTED_CH3 2
#define ADC_INJECTED_CH4 3

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* @brief initalizes the adc
	* @param adc_trigger Set the trigger for adc, if trigger is one timer then
	* this function shall only be called after that timer is initialized.
	*/
	void adc_injected(int adc_trigger);

	/**
	* @brief
	* @param channel the injected channel to get the sampled data from
	*/
	uint16_t adc_getInjectedChannelValue(int channel);

#ifdef __cplusplus
}
#endif

#endif//_CADC_STM32F3_H
