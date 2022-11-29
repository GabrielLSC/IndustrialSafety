/*
 * File:   main.c
 * Author: 21193444
 *
 * Created on 16 de Agosto de 2022, 10:42
 */


#include <xc.h>
#include "config.h"
#include "delay.h"
#include "lcd.h"
#include "sensors.h"
#include "tmr_tick.h"
#include "rfid.h"
#include "fsm_rfid.h"
#include "fsm.h"
#include "spi.h"



//FSM rfid = {rfid_read};

void main (void) 
{
 
    //Inicialização de variaveis, e funções  
    
    int perigo = 110;
    
    char state = 0;
   
    char uid = 0;
    char UID[]={"000000"};
    char TAG[]={"0000"};
    char uidAsci[]={"____________"};
    char senha[] = {/*0x81, 0xFB, 0xD5, 0x33, 0x9C, 0x00*/
                    0xDA, 0x08, 0x7e, 0x80, 0x2c, 0x00}; // 129 251 213 51 156 0
    
    TRISCbits.TRISC1 = 0;
    TRISBbits.TRISB7 = 1;
    
    ANSEL = 0;
    ANSELH = 0;
    
    
    spi_hardware_disable();
    spiSoftIniciar();
    mfrc522Iniciar();             
    lcd_init();
    sensors_init();
    tmr_tick_init();
    
    PERIGO = 1;
    
    
    while(1) 
    {  
//        rfid.func = rfid.func(&rfid);
        
        switch(state) //maquina de estados e parte principal do código
        {
            case 0: //TELA DE INICIO
    
                    lcd_print(0,3,"INDUSTRIAL");
                    lcd_print(1,4,"SAFETY");
                    delay_ms(5000);
                    state = 1;
                    lcd_clr();
                    break;
            
            
            case 1: //TELA DE ESPERA DE ACESSO
    
                    lcd_print(0,3,"ESPERANDO");
                    lcd_print(1,4,"ACESSO");
                   
                    AVISO = 0;
                    
                    procura_tag(PICC_REQIDL, TAG);
                    uid = MFRC522_AntiColl(UID);
                    
                    if(uid == 0) //TAG é econtrada
                    {
                        state = 2;
                        break;
                    }    
                    else //TAG não é encontrada
                    {
                        state = 1;
                        break;
                    }
                    
            case 2: //CHECAGEM DOS CARTÕES 
                
                    lcd_clr();

                    lcd_print(0,0,"TAG :");

                    hex2Ascii(UID,uidAsci,6);
                    
                    lcd_print(0,0,"Gabriel Lacerda");
//                    lcd_print(1,0,uidAsci);

                    delay_ms(5000);

                    if(tag_false(UID, senha) == 0) //caso a TAG do cartão seja igual a senha 
                    {
                        state = 10;
                        break;
                    }
                    else //caso a TAG do cartão não seja igual a senha 
                    {
                        state = 11;
                        break;
                    }

                    
            case 10: // ACESSO LIBERADO
                    lcd_clr(); 
                    lcd_print(0,5,"ACESSO");
                    lcd_print(1,4,"LIBERADO");
                    delay_ms(2000);
                    lcd_clr();
                    lcd_print(0,0,"MAQ. ENERGIZADA");
                    state = 20;
                    break;
                    

                
            case 11: //ACESSO NEGADO 
                    lcd_clr();
                    lcd_print(0,5,"ACESSO");
                    lcd_print(1,5,"NEGADO");
                    delay_ms(5000);
                    lcd_clr();
                    state = 1;
                    break;

            case 20: //Detecção dos Sensores 
                    
                    uts_trigger();
                    dist = 0;

                    if(prs_detect()) //sensor de presença 
                    {
                        state = 21; 
                    }
                    else
                    {
                        state = 22;
                    } 

                    if(dist > 1 && dist < perigo) //sensor ultrassonico
                    {
                        state = 23;
                    }

                    break;
                    
            case 21:
                    uts_trigger();
                    PERIGO = 0;
                    lcd_print(1,4, " ALERTA"); // caso sensor de presença detecte movimento manda 
                    state = 20;                // manda sinal digital de ALERTA
                    break;
                
            case 22: 
                    uts_trigger();
                    PERIGO = 0;                 // caso nenhum movimento seja detectado
                    lcd_print(1,4," LIVRE  ");  // o sistema fica liberado
                    state = 20;
                    break;
            
            case 23: 
                    uts_trigger();
                    PERIGO = 1;
                    lcd_clr();               // caso o sensor ultrassonico detecte algo a menos de x cm
                    lcd_print(1,5,"PARAR");  // manda sinal digital de PERIGO  
                    delay_ms(5000);
                    lcd_clr();
                    state = 1;
                    break;
        }
    }
        
        
        
// TESTE SENSOR ULTRASSONICO
//        
//        uts_trigger();
//        
//        lcd_print(0,0,"distancia");
//        
//        lcd_num(0,10,dist ,5 );

        
// TESTE SENSOR DE PRESENÇA 
//        
//
//        if(prs_detect() == 1)
//        {
//            lcd_print(1,0,"parar");
//        }
//        else
//        {
//            lcd_print(1,0,"livre");
//        }

        
////TEMPO REAL
//        
//        
//        ptr();
//        
//        if(tmr_tick(0) == 0)
//        {
//            ptr = vetor[indice];
//            tmr_tick_set(0,5);
//            ++indice;
//            indice % = 7 ;
//        } 
     

}
