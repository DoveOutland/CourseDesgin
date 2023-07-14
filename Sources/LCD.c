#include "derivative.h"      /* derivative-specific definitions */
#include "LCD.h"      

unsigned char adress_table[]=                 //定义液晶点阵的坐标
{ 
0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,      //第一行汉字位置 
0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,      //第二行汉字位置 
0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,      //第三行汉字位置 
0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F       //第四行汉字位置 
};


/*************************************************************/
/*                      初始化液晶接口                       */
/*************************************************************/
void INIT_PORT(void) 
{
 PSB_dir=1;
 SCL_dir = 1;
 SDA_dir = 1;
 CS_dir = 1;
 PSB=0;
 SCL = 0;
 SDA = 0;
 CS = 0;
}


/*************************************************************/
/*                   IIC写一个字节的数据                     */
/*************************************************************/
void write_byte(unsigned char A) 
{ 
unsigned char j; 
for(j=0;j<8;j++)        
{ 
if((A<<j)&0x80)SDA=1; 
else SDA=0; 
SCL=1;
somenop(); 
SCL=0;
somenop(); 
} 
} 

/*************************************************************/
/*                     向液晶发送数据                        */
/*************************************************************/
void write_Data(unsigned char C) 
{ 
  CS=1; 
  SCL=0; 
  write_byte(0xFA); 
  write_byte(C&0xF0);          //写高四位数据 
  write_byte(0xf0&(C<<4));            //写低四位数据 
  CS=0; 
} 

/*************************************************************/
/*                      向液晶发送命令                       */
/*************************************************************/
void write_command(unsigned char B) 
{ 
  CS=1; 
  SCL=0; 
  write_byte(0xF8); 
  write_byte(B&0xF0);        //写高四位数据 
  write_byte(0xf0&(B<<4));        //写低四位数据 
  CS=0; 
} 

/*************************************************************/
/*                         延时函数1                         */
/*************************************************************/
void delay20us(unsigned int n) 
{
    unsigned int i;
    for(i=0;i<n;i++) 
    {
        TFLG1_C0F = 1;              //清除标志位
        TC0 = TCNT + 5;             //设置输出比较时间为20us
        while(TFLG1_C0F == 0);      //等待，直到发生输出比较事件
    }
}

/*************************************************************/
/*                         延时函数2                         */
/*************************************************************/
void delay1ms(unsigned int n) 
{
    unsigned int i;
    for(i=0;i<n;i++) 
    {
        TFLG1_C0F = 1;              //清除标志位
        TC0 = TCNT + 250;             //设置输出比较时间为1ms
        while(TFLG1_C0F == 0);      //等待，直到发生输出比较事件
    }
}

/***************************************************************************/
/*                            清屏子程序                                   */
/***************************************************************************/
void lcd_clear(void)
{
    write_command(0x30);//0011,0000 功能设置，一次送8位数据，基本指令集 
    delay20us(4);       //延时80us
    write_command(0x03);//AC归0,不改变DDRAM内容 
    delay1ms(5);        //延时5ms
    write_command(0x01);//0000,0001 清DDRAM 
    delay1ms(5);        //延时5ms
    write_command(0x06);//写入时,游标右移动 
    delay20us(4);       //延时80us
    write_command(0x0C);//0000,1100  整体显示，游标off，游标位置off
    delay20us(4);       //延时80us
}

/***************************************************************************/
/*                           向LCD发送字符串                               */
/***************************************************************************/
void lcd_string(unsigned char row,unsigned char col,char *data1)   //row为写入数据所在的行数,col为写入数据所在的列数，*data1为写入的数据
{
  for(;row<4&&(*data1)!=0;row++)
  { 
      for(;col<8&&(*data1)!=0;col++)
      { 
          write_command(adress_table[row*8+col]);
          delay20us(4);       //延时80us
           
          write_Data(*data1++); 
          delay20us(4);       //延时80us
          write_Data(*data1++); 
          delay20us(4);       //延时80us
      } 
      col=0; 
  }
}












