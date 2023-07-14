#ifndef _APP_H_
#define _APP_H_
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "BSPInit.h"
void LEDandBUZZ(byte *LedData, byte BuzzFlag);
void KeyScan(void);
void delay(word ms);

#endif