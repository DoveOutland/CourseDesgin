#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "BSPInit.h"
#include "application.h"

int main(void)
{
  DisableInterrupts;
  InitConfig();
  EnableInterrupts;

  for (;;)
  {
  }
  return 0;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void TIM_IRQ(void)
{
  static word TaskLab = 0;
  static word Temperature;
  if (PITTF_PTF0 == 1)
  {
    PITTF_PTF0 = 1;
    TaskLab++;
  }
  if (TaskLab % 1 == 0) // 5ms
  {
  }
  if (TaskLab % 10 == 0) // 50ms
  {
    KeyScan();
    PWMDTY01 = CONSTRAIN(Temperature, 100, 1250) + 400;
  }
  if (TaskLab % 100 == 0) // 500ms
  {
    TaskLab = 0;
    Temperature = read_T();
  }
}

interrupt void PTH_IRQ(void)
{
  if (PIFH != 0) 
  {
    PIFH = 0xff; // 清中断
    if (KEY3 == 0)
    {
      LEDCPU = 0;
    }

    if (KEY4 == 0)
    {
      LEDCPU = 1;
    }
  }
}
#pragma CODE_SEG DEFAULT