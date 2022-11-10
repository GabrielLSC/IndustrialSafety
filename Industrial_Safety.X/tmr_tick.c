#include <xc.h>
#include "tmr_tick.h"

const unsigned int tmr_tick_reload = (0xFFFF-5000+1);
unsigned int timer[NUM_OF_TIMERS] = {0,0,0,0};

void tmr_tick_init( void )
{
    INTCONbits.GIE = 0;
    T1CONbits.TMR1GE = 0;
    T1CONbits.TMR1ON = 0;   
    T1CONbits.TMR1CS = 0;
    T1CONbits.T1CKPS = 0;
    TMR1H = (TMR_TICK_RELOAD >> 8) & 0x00FF;
    TMR1L = (TMR_TICK_RELOAD >> 0) & 0x00FF;
    INTCONbits.PEIE = 1;
    PIE1bits.TMR1IE = 1;
    INTCONbits.GIE = 1;
    T1CONbits.TMR1ON = 1;
}

void tmr_tick_int( void )
{
    TMR1H = (TMR_TICK_RELOAD >> 8) & 0x00FF;
    TMR1L = (TMR_TICK_RELOAD >> 0) & 0x00FF;
    for( char i=0; i<NUM_OF_TIMERS; i++ )
    {
        if( timer[i] )
            --timer[i];
    }
}

void tmr_tick_set( unsigned char tmr, unsigned int time )
{
    if( tmr < NUM_OF_TIMERS )
    {
        timer[tmr] = time;
    }
}

unsigned int tmr_tick( unsigned char tmr )
{
    if( tmr < NUM_OF_TIMERS )
    {
        return( timer[tmr] );
    }
    else
    {
        return( 0 );
    }
}
