#include <hidef.h>


#define  DSO       PTJ_PTJ1
#define  DSI       PTIJ_PTIJ1
#define  DSDDR     DDRJ_DDRJ1

void delay8us(unsigned int n); 
void init18b20(void);
void WR18b20(byte cmd);
unsigned char RD18b20(void);
unsigned int read_T(void);
