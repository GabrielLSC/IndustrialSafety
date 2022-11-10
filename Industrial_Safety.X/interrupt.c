/*
 * File:   interrupt.c
 * Author: 21193442
 *
 * Created on 23 de Agosto de 2022, 08:47
 */


#include <xc.h>
#include "lcd.h"
#include "delay.h"
#include "sensors.h"
#include "tmr_tick.h"

void __interrupt() isr(void)
{
    if ( INTCONbits.RBIE && INTCONbits.RBIF ) // calcula e mede a distancia do sensor ultrassnico
    {                                         // atraves do tempo de ativcação do pino echo

        if(PORTBbits.RB7)
        {
            TMR1H = 0;
            TMR1L = 0;
            time  = 0;
            T1CONbits.TMR1ON  =  1;
        } 
        else
        {
            T1CONbits.TMR1ON  = 0;
            time = TMR1H;
            time <<= 8;
            time += TMR1L;
            dist = ((((time*34717) /5000) /2) /1000) ; //Conversão do tempo para a distância 
        }
        
        INTCONbits.RBIF = 0;  
    }

    if( PIR1bits.TMR1IF ) //Interrupt utilizado para o tmr_tick()
    {
        
        PIR1bits.TMR1IF = 0;
        tmr_tick_int();
        
    }
}


//    if( INTCONbits.T0IF && INTCONbits.T0IE )
//    {
//        INTCONbits.T0IF = 0;
//        T0_int();
//    }
//    if( PIR1bits.TMR2IF && PIE1bits.TMR2IE )
//    {
//        PIR1bits.TMR2IF = 0;
//        T2_int();
//    }
//    if( PIR1bits.CCP1IF && PIE1bits.CCP1IE )
//    {
//        
//        PIR1bits.CCP1IF  = 0;
//        PORTAbits.RA0    = !PORTAbits.RA0;
//        ccp_load  ( CCPR1H, CCPR1L );
//    }

//    if( PIR1bits.TMR1IF && PIE1bits.TMR1IE )
//    {
//        PIR1bits.TMR1IF = 0;
//        TMR1H = ((65536 - 500) >> 8) & 0x00FF;
//        TMR1L = ((65536 - 500) >> 0) & 0x00FF;
//        ++time;
//    }
    

    



