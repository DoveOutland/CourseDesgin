#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "BSPInit.h"

KeyScan_t Keyscan;

void InitConfig(void)
{
    PLL_Init();
    TIM_Init();
    LEDandBUZZInit();
    KeyScanInit();
    PWM_Init();
    ETC_Init();
    KeyIRQInit();
}

void LEDandBUZZInit(void)
{
    LEDCPU_dir = 1; // 设置为输出
    BUZZ_dir = 1;
    LED_dir = 0xff; // 设置为输出
    LED = ~0x01;    // 点亮LED1
    LEDCPU = 0;
}
void KeyScanInit(void)
{
    KEY1_dir = 0; // 设置为输入
    KEY2_dir = 0; // 设置为输入
    Keyscan.data = 0x01;
    Keyscan.KEY1_last = 1;
    Keyscan.KEY2_last = 1;
    Keyscan.mode = 1;
}
void KeyIRQInit(void)
{
    KEY1_dir = 0; // 设置为输入
    KEY2_dir = 0;
    KEY3_dir = 0;
    KEY4_dir = 0;
    PPSH = 0x00; // 极性选择寄存器,选择下降沿;
    PIFH = 0x0f; // 对PIFH的每一位写1来清除标志位;
    PIEH = 0x0f; // 中断使能寄存器;
}
void PLL_Init(void)
{
    CLKSEL &= 0x7f; // 设置OSCCLK作为系统时钟
    PLLCTL &= 0x8F; // 禁止锁相环
    CRGINT &= 0xDF;

#if (BUS_CLOCK == 72000000)
    SYNR = 0xc8;
#elif (BUS_CLOCK == 64000000)
    SYNR = 0xc7;
#elif (BUS_CLOCK == 56000000)
    SYNR = 0xc6;
#elif (BUS_CLOCK == 48000000)
    SYNR = 0xc5;
#elif (BUS_CLOCK == 40000000)
    SYNR = 0x44;
#elif (BUS_CLOCK == 32000000)
    SYNR = 0x43;
#elif (BUS_CLOCK == 24000000)
    SYNR = 0x42;
#elif (BUS_CLOCK == 16000000)
    SYNR = 0x01;
#endif
    REFDV = 0x81;
    PLLCTL |= 0x70; // 使能锁相环
    asm NOP;
    asm NOP;
    while (!(CRGFLG & 0x08))
        ;           // PLLCLK锁定
    CLKSEL |= 0x80; // 设置PLLCLK为系统时钟
}
void TIM_Init(void)
{

    PITMTLD0 = 159;     // 为0通道8位计数器赋值
    PITLD0 = 719;       // 为0通道16位计数器赋值
    PITMUX_PMUX0 = 0;   // 第0通道使用微计数器0
    PITCE_PCE0 = 1;     // 第0通道计数器工作
    PITCFLMT = 0X80;    // 使能周期中断定时器
    PITINTE_PINTE0 = 1; // 0通道定时器定时中断被使能
}
void PWM_Init(void)
{
    PWMCTL_CON01 = 1;
    PWMCTL_CON23 = 1;

    PWMPOL_PPOL1 = 1; // 高电平有效
    PWMPOL_PPOL3 = 0; // 低电平有效

    PWMPRCLK = 0x22; // 8MHz
    PWMSCLA = 1;     // SASB4MHz
    PWMSCLB = 1;
    PWMCLK = 0x0a;
    PWMCAE = 0x00;

    PWMPER01 = 1600; // 1Hz
    PWMDTY01 = 1500;  // 占空比 = PWMDTY01/PWMPER01
    PWMPER23 = 1600;
    PWMDTY23 = 1500;

    PWME_PWME1 = 1;
    PWME_PWME3 = 1;
}
void ETC_Init(void)
{
    TSCR1_TFFCA = 1; // 定时器标志位快速清除
    TSCR1_TEN = 1;   // 定时器使能位. 1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
    TIOS = 0xff;     // 指定所有通道为输出比较方式
    TCTL1 = 0x00;    // 后四个通道设置为定时器与输出引脚断开
    TCTL2 = 0x00;    // 前四个通道设置为定时器与输出引脚断开
    TIE = 0x00;      // 禁止所有通道定时中断
    TSCR2 = 0x07;    // 预分频系数pr2-pr0:111,,时钟周期为4us,
    TFLG1 = 0xff;    // 清除各IC/OC中断标志位
    TFLG2 = 0xff;    // 清除自由定时器中断标志位
}