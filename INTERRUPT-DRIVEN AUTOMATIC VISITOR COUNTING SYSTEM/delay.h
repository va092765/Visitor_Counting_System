#include<lpc21xx.h>
void delay_s(unsigned int);
void delay_ms(unsigned int);
void delay_s(unsigned int s)
{
T0PR=15000000-1;
T0TCR=0X1;
while(T0TC<s);
T0TCR=0X3;
T0TCR=0X0;
}
void delay_ms(unsigned int ms)
{
T0PR=15000-1;
T0TCR=0X1;
while(T0TC<ms);
T0TCR=0X3;
T0TCR=0X0;
}