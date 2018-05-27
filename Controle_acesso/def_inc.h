/*
 * portas.h
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




#endif /* PORTAS_H_ */