/*
 * File:   prs.c
 * Author: 21193442
 *
 * Created on 19 de Agosto de 2022, 09:23
 */


#include <xc.h>
#include "delay.h"
#include "sensors.h"



int t_sensor;

long dist;
long time;

unsigned char ret;

void sensors_init (void) 
{
    AVISO = 0;
    PRS_IN = 0;
 
    
    t_sensor = 0;
    ret = 0;
    
    INTCONbits.GIE    =  0;
    
    TRISAbits.TRISA3 = 1; // Define a porta RA3 como entrada
    TRISCbits.TRISC0 = 0; // Define a porta RC2 como saida
    TRISAbits.TRISA2 = 0;  // Define a porta RA2 
    
    T1CONbits.TMR1CS  =  0;
    T1CONbits.TMR1GE  =  0;
    T1CONbits.T1CKPS  =  0;
    T1CONbits.TMR1ON  =  0;
    
    TRISBbits.TRISB7 = 1;
    INTCONbits.RBIE  = 1;
    IOCBbits.IOCB7   = 1;

    INTCONbits.PEIE =  1; 
    INTCONbits.GIE  =  1;
}

unsigned char prs_detect( void )
{
    if(PRS_IN == 1)
    {
        t_sensor = 3000;
        AVISO = 1;
    }
    
    else
    {
        --t_sensor;
        delay_ms(1);
        
        if(t_sensor == 0)
        {    
            AVISO = 0;
        }
    }
    
    ret = AVISO;
    
    return( ret );
}

void uts_trigger (void)  // Manda um sinal de 10us para 
{                        // o pino trigger do sensor ultrassonico
    UTS_TRIGGER = 1;
    __delay_us(10);
    UTS_TRIGGER = 0;
    __delay_us(10);
}


