/*
 * File:   fsm_rfid.c
 * Author: 21193442
 *
 * Created on 25 de Outubro de 2022, 10:41
 */


#include <xc.h>
#include "fsm.h"
#include "rfid.h"
#include "lcd.h"
#include "tmr_tick.h"

char uid = 0;
char UID[]={"000000"};
char TAG[]={"0000"};
char uidAsci[]={"____________"};


//struct corsiT;
//{
//    int tempo;
//    char saidas;
//} corsi = { 1000, 0x0F };
//
//struct lacerdaT
//{
//    char vetor[4];
//    int * ptr;
//} lacerda;

void * rfid_read (void * p) 
{
    tmr_tick_set(0,500);
    procura_tag(PICC_REQIDL, TAG);
    
    uid = MFRC522_AntiColl(UID);
    lcd_print(0,15,"<");
    
    if(!tmr_tick(0))
    {
        return(rfid_display);
    }
    
    else
    {
        return(rfid_read);
    }   
}

void * rfid_read_wait (void * p) 
{
//    ((FSM *)p)->arg = &corsi;
    if(!tmr_tick(0))
    {
        return(rfid_display);
    }
    
    else
    {
        return(rfid_read_wait);
    }   
}

void * rfid_display (void * p) 
{
    tmr_tick_set(0,500);
    lcd_num(0,0,uid,1);
    lcd_print(0,15,">");
    
    if(uid == 0)
    {
        hex2Ascii(UID,uidAsci,6);
        lcd_print(1,3,uidAsci);
    }
    if(!tmr_tick(0))
    {
        return(rfid_read);
    }
    else
    {
        return(rfid_display);
    }
}

void * rfid_display_wait (void * p) 
{
    if(!tmr_tick(0))
    {
        //lcd_clr();
        return(rfid_read);
    }
    
    else
    {
        //lcd_clr();
        return(rfid_display_wait);
    }   
}




