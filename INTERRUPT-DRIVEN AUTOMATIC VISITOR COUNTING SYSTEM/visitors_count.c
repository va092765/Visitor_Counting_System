#include"lch.h"
volatile unsigned char flag1=0;
volatile unsigned char flag2=0;
#define ROOM_LIGHT_LED 1<<10
#define INDICATION_LED 1<<11
#define SWITCH 17
int c=0;
void LCD_TITLE(void);
unsigned int entry_count=0,exit_count=0;
void ext_int0_isr(void) __irq
{
 EXTINT=0X01;
 flag1=1;
 VICVectAddr=0;
}
void ext_int1_isr(void) __irq
{
 EXTINT=0X02;
 flag2=1;
 VICVectAddr=0;
}
int main()
{
 IODIR0 |= ROOM_LIGHT_LED|INDICATION_LED;
 IOSET0=ROOM_LIGHT_LED|INDICATION_LED;
 LCD_INIT();
 LCD_TITLE();
 PINSEL0 |= 0X20000000;
 PINSEL1 |= 0X1;
 VICIntSelect=0;
 VICVectCntl0=(1<<5)|14;
 VICVectAddr0=(unsigned long)ext_int0_isr;
 VICVectCntl1=(1<<5)|15;
 VICVectAddr1=(unsigned long)ext_int1_isr;
 EXTMODE=0X03;
 EXTPOLAR=0X03;
 VICIntEnable=(1<<14)|(1<<15);
 while(1)
 {
  if(flag1==1)
  {
   entry_count++;
   c++;
   IOCLR0=INDICATION_LED;
   delay_ms(500);
   IOSET0=INDICATION_LED;
   delay_ms(500);
   flag1=0;
  }
  if(flag2==1)
  {
   if(c>0)
   {
    c--;
    exit_count++;
    IOCLR0=INDICATION_LED;
    delay_ms(500);
    IOSET0=INDICATION_LED;
    delay_ms(500);
   }
   flag2=0;
  }
  if((flag1==0)&&(flag2==0))
  {
   (c>0)?(IOCLR0=ROOM_LIGHT_LED):(IOSET0=ROOM_LIGHT_LED);
   LCD_COMMAND(0X80);
   LCD_STR("VISITORS COUNT");
   LCD_COMMAND(0XC0);
   LCD_INTEGER(c);
  }
  if(((IOPIN0>>SWITCH)&1)==0)
  {
  entry_count--;
  exit_count--;
   LCD_COMMAND(0X01);
   LCD_COMMAND(0X80);
   LCD_STR("IN:");
   LCD_COMMAND(0xC0);
   LCD_INTEGER(entry_count);
   LCD_COMMAND(0X94);
   LCD_STR("OUT:");
   LCD_COMMAND(0xD4);
   LCD_INTEGER(exit_count);
   delay_s(3);
   LCD_COMMAND(0X01);
  }
 }
}
void LCD_TITLE()
{
 LCD_COMMAND(0X80);
 LCD_STR("INTERRUPT DRIVEN AUTOMATIC VISITOR COUNT SYSTEM");
 delay_s(3);
 LCD_COMMAND(0X01);
}



