#ifndef RFID_H
#define RFID_H


/* MFRC522 */
// Page 0: Command and Status
#define RESERVED00				0x00			// 
#define COMMANDREG				0x01			// 
#define COMMIENREG				0x02			// 
#define DIVLENREG				0x03			// 
#define COMMIRQREG				0x04			// 
#define DIVIRQREG				0x05			// 
#define ERRORREG				0x06			// 
#define STATUS1REG				0x07			// 
#define STATUS2REG				0x08			// 
#define FIFODATAREG				0x09			// 
#define FIFOLEVELREG			0x0A			// 
#define WATERLEVELREG			0x0B			// 
#define CONTROLREG				0x0C			// 
#define BITFRAMINGREG			0x0D			// 
#define COLLREG					0x0E			// 
#define RESERVED01				0x0F			// 

// PAGE 1: Command
#define RESERVED10				0x10			// 
#define MODEREG					0x11			// 
#define TXMODEREG				0x12			// 
#define RXMODEREG				0x13			// 
#define TXCONTROLREG			0x14			// 
#define TXAUTOREG				0x15			// 
#define TXSELREG				0x16			// 
#define RXSELREG				0x17			// 
#define RXTHRESHOLDREG			0x18			// 
#define DEMODREG				0x19			// 
#define RESERVED11				0x1A			// 
#define RESERVED12				0x1B			// 
#define MIFAREREG				0x1C			// 
#define RESERVED13				0x1D			// 
#define RESERVED14				0x1E			// 
#define SERIALSPEEDREG			0x1F			// 
// PAGE 2: CFG
#define RESERVED20				0x20			// 
#define CRCRESULTREGM			0x21			// 
#define CRCRESULTREGL			0x22			// 
#define RESERVED21				0x23			// 
#define MODWIDTHREG				0x24			// 
#define RESERVED22				0x25			// 
#define RFCFGREG				0x26			// 
#define GSNREG					0x27			// 
#define CWGSPREG				0x28			// 
#define MODGSPREG				0x29			// 
#define TMODEREG				0x2A			// 
#define TPRESCALERREG			0x2B			// 
#define TRELOADREGH				0x2C			// 
#define TRELOADREGL				0x2D			// 
#define TCOUNTERVALUEREGH		0x2E			// 
#define TCOUNTERVALUEREGL		0x2F			// 

// PAGE 3: TEST REGISTER
#define RESERVED30				0x30			// 
#define TESTSEL1REG				0x31			// 
#define TESTSEL2REG				0x32			// 
#define TESTPINENREG			0x33			// 
#define TESTPINVALUEREG			0x34			// 
#define TESTBUSREG				0x35			// 
#define AUTOTESTREG				0x36			// 
#define VERSIONREG				0x37			// 
#define ANALOGTESTREG			0x38			// 
#define TESTDAC1REG				0x39			// 
#define TESTDAC2REG				0x3A			// 
#define TESTADCREG				0x3B			// 
#define RESERVED31				0x3C			// 
#define RESERVED32				0x3D			// 
#define RESERVED33				0x3E			// 
#define RESERVED34				0x3F			// 

// PAGE 4: MF522 Command word
#define PCD_IDLE				0x00			// NO action; Cancel the current command
#define PCD_AUTHENT				0x0E			// Authentication Key
#define PCD_RECEIVE				0x08			// Receive Data
#define PCD_TRANSMIT			0x04			// Transmit data
#define PCD_TRANSCEIVE			0x0C			// Transmit and receive data,
#define PCD_RESETPHASE			0x0F			// Reset
#define PCD_CALCCRC				0x03			// CRC Calculate

// PAGE 5: Mifare_One card command word
#define PICC_REQIDL				0x26			// Find the antenna area does not enter hibernation
#define PICC_REQALL				0x52			// Find all the cards antenna area
#define PICC_ANTICOLL			0x93			// Anti-collision
#define PICC_SElECTTAG			0x93			// Election card
#define PICC_AUTHENT1A			0x60			// Authentication key A
#define PICC_AUTHENT1B			0x61			// Authentication key B
#define PICC_READ				0x30			// Read Block
#define PICC_WRITE				0xA0			// Write block
#define PICC_DECREMENT			0xC0			// Debit
#define PICC_INCREMENT			0xC1			// Recharge
#define PICC_RESTORE			0xC2			// Transfer block data to the buffer
#define PICC_TRANSFER			0xB0			// Save the data in the buffer
#define PICC_HALT				0x50			// Sleep

/* Geral */
#define LED_LIGADO			0		// valor para acionamento do led
#define LED_DESLIGADO		1
#define RELE_LIGADO			1		// valor para acionamento do rele
#define RELE_DESLIGADO		0
#define MODO_PROG			1		// valor para modo de programacao
#define MODO_NORMAL			0		// valor para modo normal
#define TAGMESTREGRAVADA	170		// um numero qualquer para indicar a condicao
#define POSICAO_TAGMESTRE	2		// localizado tag mestre no endereço 2 da eeprom
#define TAGDESCONHECIDA		0x7E	// tag ainda nao foi gravada na eeprom
#define ESCREVER			0		// escrever dados
#define LER					1		// ler dados
#define APAGAR_EEPROM		0		// Apagar todas as tags da eeprom.
#define APAGAR_TAG_MESTRE	1		// Apagar a tag mestre da eeprom.
#define DESLOCAMENTO		2		// indica deslocamento na posicao inicial da eeprom

//MFRC-522 Codigos de erros da comunicacao
#define MI_OK				0		// Sem erros.
#define MI_NOTAGERR			1		// Nao existe tag proximo ao leitor.
#define MI_ERR				2		// Erro na comunicacao.
#define MAX_LEN				16		// Tamanho maximo .




void delay_piscal(void);							// Rotina de delay de 200 ms.
void delay_1seg(void);							// Rotina de delay de 1 segundo.
void mfrc522ClrBit(char end, char mascara); // Limpa um bit .
void mfrc522SetBit(char end, char mascara); // Ativa um bit no registro
void mfrc522AntOn(void); // Liga a antena.
void mfrc522AntOff(void); // Desliga a antena.
void mfrc522Rst(void); // Reset por software.
void mfrc522Iniciar(void); // Inicializa o MFRC522.
void eepromEscrever(char Address, char Data); // Grava um dado no endereco da EEprom.
char eepromLer(char Address); // Le um dado no endereco da EEprom.
void eepromApagar(void); // Apaga a EEprom.
char tagTxCmd(char cmd, char *data, char dlen, char *result, char *rlen);
char tagLocalizar(void); // Busca UID gravada na Eeprom.
void tagMasterWr(void); // Grava a UID de Tag mestre na Eeprom.
void tagSlaverWr(void); // Grava a UID de Tag escrava na Eeprom.
char procura_tag(char modo, char *data);											// 
char anti_colisao(char *mBuf);
char get_UID(void); // Obter UID da tag no campo do leitor.
char mfrc522Uid(char *vlrAsc);
void testa_botao_del(char modo);
static void MFRC522_Wr(char addr, char value);
static char MFRC522_Rd(char addr);
static void MFRC522_Clear_Bit(char addr, char mask);
static void MFRC522_Set_Bit(char addr, char mask);
void MFRC522_Reset(void);
void MFRC522_AntennaOn(void);
void MFRC522_AntennaOff(void);
void MFRC522_Init();
char MFRC522_ToCard(char command, char *sendData, char sendLen, char *backData, char *backLen);
char MFRC522_Request(char reqMode, char *TagType);
void MFRC522_CRC(char *dataIn, char length, char *dataOut);
char MFRC522_SelectTag(char *serNum);
void MFRC522_Halt(); //hibernacao
char MFRC522_Auth(char authMode, char BlockAddr, char *Sectorkey, char *serNum);
char MFRC522_Write(char blockAddr, char *writeData);
char MFRC522_Read(char blockAddr, char *recvData);
char MFRC522_AntiColl(char *serNum);
char MFRC522_isCard(char *TagType);
char MFRC522_ReadCardSerial(char *str);
void hex2Ascii(char *strIn, char *strOut, char cntDig);
void eepromLoad(void);
char tagSearch(char *tagVlr);	// Procura TAG na E2PROM

char tag_false (char* p1, char * p2);

#endif