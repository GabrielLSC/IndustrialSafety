#ifndef EEPROM_H
#define EEPROM_H

/* EEPROM */
void eepromEscrever(char Address, char Data); // Grava um dado no endereco da EEprom.

char eepromLer(char Address);                 // Le um dado no endereco da EEprom.

void eepromApagar(void);                      // Apaga a EEprom.

//char matEeprom[]=

void eepromLoad(void);

#endif
