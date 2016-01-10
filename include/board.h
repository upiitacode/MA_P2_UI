#ifndef _BOARD_H
#define _BOARD_H

#define LED_STATE_OFF 0
#define LED_STATE_ON 1

#ifdef __cplusplus
extern "C" {
#endif

void led_init(void);

void led_setState(int led_state);


#ifdef __cplusplus
}
#endif

#endif// _BOARD_H
