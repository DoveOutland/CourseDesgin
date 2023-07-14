#include "application.h"

void LEDandBUZZ(byte *LedData, byte BuzzFlag)
{
    BUZZ = BuzzFlag;
    if (BuzzFlag == 1)
    {
        LED = *LedData;
    }
    else
    {
        LED = ~*LedData;
    }

    *LedData = *LedData << 1;
    if (*LedData == 0x00)
    {
        *LedData = 0x01;
    }
}

void KeyScan(void)
{

    if (KEY1 == 0 && Keyscan.KEY1_last == 1) // 按键F1按下
    {
        Keyscan.mode = 1;
    }
    if (KEY2 == 0 && Keyscan.KEY2_last == 1)
    {
        Keyscan.mode = 2;
    }
    Keyscan.KEY1_last = KEY1;
    Keyscan.KEY2_last = KEY2;

    if (Keyscan.mode == 1)
    {
        LEDandBUZZ(&Keyscan.data, 1);
    }
    else
    {
        LEDandBUZZ(&Keyscan.data, 0);
    }
}

void delay(word ms)
{
    unsigned int i;
    for (i = 0; i < ms; i++)
    {
        TFLG1_C0F = 1;
        TC0 = TCNT + 250; // 1ms
        while (TFLG1_C0F == 0); 
    }
}