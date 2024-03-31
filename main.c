/*
 * 1614_20k_tca.c
 *
 * Created: 2024-03-20 09:21:50
 * Author : michael
 */ 


#define PERIOD_EXAMPLE_VALUE (0x00A6)
#include <avr/io.h>
#include <avr/interrupt.h>
/*Using default clock 3.33MHz */
void TCA0_init(void);
void PORT_init(void);

void TCA0_init(void)
{
	/* enable overflow interrupt */
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	
	/* set Normal mode */
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
	
	/* disable event counting */
	TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);
	
	/* set the period */
	TCA0.SINGLE.PER = PERIOD_EXAMPLE_VALUE;
	
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV2_gc   /* set clocksource (sys_clk/256) */
	| TCA_SINGLE_ENABLE_bm; /* start timer */
}
void PORT_init(void)
{
	/* set pin 7 of PORT A as output */
	PORTA.DIR = 0b10000000; // |= PIN7_bm;
}
ISR(TCA0_OVF_vect)
{
	/* Toggle PIN 7 of PORT A */
	//PORTA.OUTTGL = PIN7_bm;
	PORTA_OUTSET = 0b10000000;
	PORTA.OUTCLR = 0b10000000;
	
	/* The interrupt flag has to be cleared manually */
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}


int main(void)
{
    PORT_init();
    
    TCA0_init();
    
    /* enable global interrupts */
    sei();
    while (1) 
    {
    }
}

