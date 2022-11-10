
/*
 * File:   spiSoft_v01.c
 * Author: 21193444
 *
 * Created on 11 de Outubro de 2022, 08:05
 */


#include <xc.h>
#include <pic16f887.h>
#include "delay.h"
#include "spi.h"


/* SPI por software */
void spiSoftClk(void)							// Gera pulso de clock para o SPI.
{
	pinSck_ = 1;
	__delay_us(1);								// +- 110kBps (10=~100khz)
	pinSck_ = 0;
}

void spi_hardware_disable (void)
{
    C2ON   =  0;
    ANSELH =  0;
    ANSEL  =  0;
    SSPEN  =  0;
    SSPIE  =  0;
}

void spiSoftIniciar(void)						// Inicializa o SPI.
{
   
	pinMisoCfg = 1;								// Configura pino como entrada.
	pinMosiCfg = 0;								// Configura pino como saida.
	//pinRstCfg = 0;								// Configura pino como saida.
	pinSckCfg = 0;								// Configura pino como saida.
	pinSdaCfg = 0;								// Configura pino como saida.
	pinMosi = 0;								// Inicializa o pino.
	pinSck_ = 0;								// Inicializa o pino.
	pinSda_ = 0;								// Inicializa o pino.
	//pinRst = 0;									// Pino Reset: Reset ativo.
	__delay_us(100);							// Aguarda...
	//pinRst = 1;									// Pino Reset: Reset inativo.
	__delay_ms(1);								// Aguarda...
}

void spiSoftTxCmd(char end, char oper) // Envio de um Comando SPI
{
	char reg, a;
	pinSda_ = 0;
	reg = end << 1;
	if (oper)reg = reg | 0x80; // Bit7 deve ser '1' para ler.
	else reg = reg & 0x7E; // Bit7 deve ser '0' para escrever. era: 0b0111 1110

	for (a = 0; a < 8; a++)
	{
		if (reg & 0x80)pinMosi = 1; // era: 0b10000000
		else pinMosi = 0;
		reg = reg << 1;
		spiSoftClk();
	}
}

void spiSoftTxDat(char dado) // Envia um Byte na SPI
{
	char reg, a;
	reg = dado;
	for (a = 0; a < 8; a++)
	{
		if (reg & 0x80)pinMosi = 1; // era: 0b10000000
		else pinMosi = 0;
		reg = reg << 1;
		spiSoftClk();
	}
}

char spiSoftRxDat(void) // Le um dado na SPI
{
	char rc, a;
	for (a = 0; a < 8; a++) // laco de leitura dos 8 bits.
	{
		rc = rc << 1; // Desloca bit para compor o valor.
		if (pinMiso)rc++;
		spiSoftClk();
	}
	return (rc); // Retorna o valor lido.
}
