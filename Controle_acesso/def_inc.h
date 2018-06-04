/*
 * portas.h
 *
 *Arquivo com os includes e macros necessários no projeto
 *
 * Created: 26/05/2018 01:04:17
 *  Author: RodolfoSchiavi
 */ 


#ifndef def_inc_H_
#define def_inc_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <avr/interrupt.h>

using namespace std;

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

#define set_bit(adress,bit) (adress|=(1<<bit))
#define clr_bit(adress,bit) (adress&=~(1<<bit))
#define clp_bit(adress,bit) (adress^=(1<<bit))
#define tst_bit(adress,bit)  (adress&(1<<bit))
#define LED PC3

#define DADOS_LCD PORTB //8 bits de dados do LCD na porta D
#define CONTR_LCD PORTD //os pinos de controle est?o no PORTB
#define RS PORTD2 //pino de instru??o ou dado para o LCD
#define E PORTD3 //pino de enable do LCD
#define pulso_enable() _delay_us(10); set_bit(CONTR_LCD,E); _delay_us(10); clr_bit(CONTR_LCD,E); _delay_us(450);
#define linha_inf lcd.cmd_LCD(0x80|0x40,0) //Macro para setar o cursor na linha debaixo do display fora da classe LCD



#endif /* PORTAS_H_ */