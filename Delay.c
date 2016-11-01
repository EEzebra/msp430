#include"Delay.h"

void delay(uint n)
{
  while(n--);
  return;
}

//-----------------------------------------
//us—” ±
void delay_ms(uint n)
{
  while(n--)
  {
    delay(2000);
  }
}

//-----------------------------------------
//ms—” ±
void delay_s(uint n)
{
  while(n--)
  {
    delay_ms(60);
  }
}
