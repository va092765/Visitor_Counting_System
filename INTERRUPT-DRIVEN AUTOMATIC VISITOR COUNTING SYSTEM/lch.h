#include<LPC21XX.H>
#include "delay.h"
#define LCD_D 0xff
#define RS 1<<8
#define E 1<<9
void LCD_INIT(void);
void LCD_COMMAND(unsigned char cmd);
void LCD_DATA(unsigned char data);
void LCD_STR(unsigned char *str);
void LCD_INTEGER(int num);
void LCD_FLOAT(double num);
void LCD_INIT(void)
{
PINSEL0 |= 0;
IODIR0 |= LCD_D|RS|E;
LCD_COMMAND(0X01);
LCD_COMMAND(0X02);
LCD_COMMAND(0X0C);
LCD_COMMAND(0X38);
}
void LCD_COMMAND(unsigned char cmd)
{
IOCLR0=LCD_D;
IOSET0=cmd;
IOCLR0=RS;
IOSET0=E;
delay_ms(2);
IOCLR0=E;
}
void LCD_DATA(unsigned char data)
{
IOCLR0=LCD_D;
IOSET0=data;
IOSET0=RS;
IOSET0=E;
delay_ms(2);
IOCLR0=E;
}
void LCD_INTEGER(int number)
{
unsigned char a[5];
signed char i=0;
if(number==0)
LCD_DATA('0');
else{
if(number<0){
LCD_DATA('-');
number=-number;
}
while(number>0)
{
a[i++]=number%10;
number=number/10;
}
for(--i;i>=0;i--){
LCD_DATA(a[i]+48);
}
}
}
void LCD_FLOAT(double f)
{
int temp;
temp=f;
LCD_INTEGER(temp);
LCD_DATA('.');
temp=(f-temp)*1000;
LCD_INTEGER(temp);
}

void LCD_STR(unsigned char *s){

unsigned char count=0;
while(*s){
LCD_DATA(*s++);
count++;

if(count==20){
LCD_COMMAND(0XC0);
}
else if(count==40){
LCD_COMMAND(0X94);
}
else if(count==60){
LCD_COMMAND(0XD4);
}
}
}