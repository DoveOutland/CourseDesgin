#ifndef _BSP_H_
#define _BSP_H_
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "LCD.h"
#include "18B20.h"

#define BUS_CLOCK 72000000 // 总线频率
#define OSC_CLOCK 16000000 // 晶振频率
#define LEDCPU PORTK_PK4
#define LEDCPU_dir DDRK_DDRK4
#define BUZZ PORTK_PK5
#define BUZZ_dir DDRK_DDRK5
#define LED PORTB
#define LED_dir DDRB
#define KEY1 PTIH_PTIH3
#define KEY2 PTIH_PTIH2
#define KEY3 PTIH_PTIH1
#define KEY4 PTIH_PTIH0
#define KEY1_dir DDRH_DDRH3
#define KEY2_dir DDRH_DDRH2
#define KEY3_dir DDRH_DDRH1
#define KEY4_dir DDRH_DDRH0
#define CONSTRAIN(x, min, max) ((x > max) ? max : (x < min ? min : x))

typedef struct
{
    byte data;
    byte mode;
    byte KEY1_last;
    byte KEY2_last;
} KeyScan_t;
extern KeyScan_t Keyscan;

void InitConfig(void);

void LEDandBUZZInit(void);
void KeyScanInit(void);
void KeyIRQInit(void);
void PLL_Init(void);
void TIM_Init(void);
void PWM_Init(void);
void ETC_Init(void);

#endif