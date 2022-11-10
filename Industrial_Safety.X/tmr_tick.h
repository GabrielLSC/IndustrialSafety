#ifndef TMR_TICK_H
#define TMR_TICK_H

#define TMR_TICK_RELOAD     (0xFFFF-5000+1)

#define TMR_TICK_0          0
#define TMR_TICK_1          1
#define TMR_TICK_2          2
#define TMR_TICK_3          3
#define NUM_OF_TIMERS       4

void tmr_tick_init( void );
void tmr_tick_int( void );
void tmr_tick_set( unsigned char tmr, unsigned int time );
unsigned int tmr_tick( unsigned char tmr );

#endif