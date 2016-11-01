#include<msp430FR5725.h>
#include"LED.h"
void led_mode1_init(void)
{
    P1DIR |= BIT0;
//    P1OUT |= BIT0+BIT1;
    P1SEL0 |= BIT0;
    
    TA0CCTL0 = CCIE;
    
    TA0CCR0 = 10000+1;
    
    TA0CCTL1 = OUTMOD_7;
    TA0CCR1 = 10000;

    TA0CTL = TASSEL_2 + MC_1 + TACLR;
    //TA0CTL |= MC_0 + TACLR;
    //TA0CTL &= ~TAIE;
}

void led_mode1_off(void)
{
    TA0CTL |= MC_0 + TACLR;
    TA0CTL &= ~TAIE;
}


#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    if(TA0CCR1)
    {
        TA0CCR1=TA0CCR1-50;
    }
    else
    {
        TA0CCR1 = 10000;
        if((TA0CCTL1&OUTMOD_7)==OUTMOD_7)
        {
            TA0CCTL1=OUTMOD_3;
        }
        else
        {
            TA0CCTL1 = OUTMOD_7;
        }
    }
}

