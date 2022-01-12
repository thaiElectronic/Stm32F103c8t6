#ifndef _TOUCH_MYONE_H_
#define _TOUCH_MYONE_H_

#include <stm32f10x.h>

#define T_IRQ_Pin GPIO_Pin_3
#define T_IRQ_GPIO_Port GPIOA
#define T_CLK_Pin GPIO_Pin_5
#define T_CLK_GPIO_Port GPIOA
#define T_MISO_Pin GPIO_Pin_6
#define T_MISO_GPIO_Port GPIOA
#define T_MOSI_Pin GPIO_Pin_7
#define T_MOSI_GPIO_Port GPIOA
#define T_CS_Pin GPIO_Pin_4
#define T_CS_GPIO_Port GPIOA

#define TP_CLK_PORT								GPIOA
#define TP_CLK_PIN								T_CLK_Pin

#define TP_CS_PORT								GPIOA
#define TP_CS_PIN									T_CS_Pin

#define TP_MISO_PORT							GPIOA
#define TP_MISO_PIN								T_MISO_Pin

#define TP_MOSI_PORT							GPIOA
#define TP_MOSI_PIN								T_MOSI_Pin

#define TP_IRQ_PORT								GPIOA
#define TP_IRQ_PIN								T_IRQ_Pin

#define XPT2046_HOR_RES     320
#define XPT2046_VER_RES     240
#define XPT2046_X_MIN       300
#define XPT2046_Y_MIN       200
#define XPT2046_X_MAX       3800
#define XPT2046_Y_MAX       3800
#define XPT2046_AVG         4
#define XPT2046_INV         0

int16_t avg_buf_x[XPT2046_AVG];
int16_t avg_buf_y[XPT2046_AVG];
uint8_t avg_last;

#define Y 0x90
#define X 0xD0

#define CS_TOUCH_SELECT()  LL_GPIO_ResetOutputPin(GPIOB, XPT2046_CS_Pin)
#define CS_TOUCH_DESELECT()  LL_GPIO_SetOutputPin(GPIOB, XPT2046_CS_Pin)

#endif





