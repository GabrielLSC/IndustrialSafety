/*
 * File:   eeprom.c
 * Author: 21193444
 *
 * Created on 21 de Setembro de 2022, 07:44
 */


#include <xc.h>
#include "eeprom.h"
#include "config.h"
#include "delay.h"

/* EEPROM */
void eepromEscrever(char Address, char Data) // Grava um dado no endereco da EEprom.
{
	while (EECON1bits.WR); // Waits Until Last Attempt To Write Is Finished
	EEADR = Address; // Writes The Addres To Which We'll Wite Our Data
	EEDATA = Data; // Write The Data To Be Saved
	EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Not The Program Memory
	EECON1bits.WREN = 1; // Enable The Operation !
	INTCONbits.GIE = 0; // Disable All Interrupts Untill Writting Data Is Done
	EECON2 = 0x55; // Part Of Writing Mechanism..
	EECON2 = 0xAA; // Part Of Writing Mechanism..
	EECON1bits.WR = 1; // Part Of Writing Mechanism..
	INTCONbits.GIE = 1; // Re-Enable Interrupts
	EECON1bits.WREN = 0; // Disable The Operation
	EECON1bits.WR = 0; // Ready For Next Writting Operation
}

char eepromLer(char Address) // Le um dado no endereco da EEprom.
{
	char Data;
	EEADR = Address; // Write The Address From Which We Wonna Get Data
	EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Not The Program Memory
	EECON1bits.RD = 1; // Start The Read Operation
	Data = EEDATA; // Read The Data
	__delay_ms(1);
	return Data;
}

void eepromApagar(void) // Apaga a EEprom.
{
	char a;
	for (a = 0; a < 128; a++)
	{
		eepromEscrever(a, 0XFF); //zera eeprom do pic
	}
}

char matEeprom[]=
{
	0xFF,0xFF,0xFF,0xFF,0xFF, // 00...04
	0xFF,0xFF,0xFF,0xFF,0xFF, // 05...09
	0xFF,0xFF,0xFF,0xFF,0xFF, // 10...14
	0xFF,0xFF,0xFF,0xFF,0xFF, // 15...19
	0xFF,0xFF,0xFF,0xFF,0xFF, // 20...24
	0xFF,0xFF,0xFF,0xFF,0xFF, // 25...29
	0xFF,0xFF,0xFF,0xFF,0xFF, // 30...34
	0xFF,0xFF,0xFF,0xFF,0xFF, // 35...39
	0xFF,0xFF,0xFF,0xFF,0xFF, // 40...44
	0xFF,0xFF,0xFF,0xFF,0xFF, // 45...49
	0xFF,0xFF,0xFF,0xFF,0xFF  // 50...54
};

void eepromLoad(void)
{
	char x,y;
	for(x=0;x<55;x+=5)
	{
		for(y=0;y<5;y++)matEeprom[x+y]=eepromLer(x+y);
	}
}

