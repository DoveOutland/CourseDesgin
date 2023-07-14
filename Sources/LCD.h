#include <hidef.h>      /* common defines and macros */

#define SCL PTJ_PTJ7         //IIC的时钟线
#define SDA PTJ_PTJ6         //IIC的数据线
#define CS PTM_PTM2          //片选信号
#define SCL_dir DDRJ_DDRJ7
#define SDA_dir DDRJ_DDRJ6
#define CS_dir DDRM_DDRM2
#define PSB PTM_PTM3
#define PSB_dir DDRM_DDRM3
#define somenop(); asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");


void INIT_PORT(void); 
void write_byte(unsigned char A); 
void write_Data(unsigned char b); 
void write_command(unsigned char b); 
void lcd_clear(void);
void lcd_string(unsigned char row,unsigned char col,char *data1);
void delay20us(unsigned int n);
void delay1ms(unsigned int n); 
void lcd_picture(void);  
 

