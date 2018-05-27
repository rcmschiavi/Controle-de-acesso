/*
 * LCD.h
 *
 * Created: 26/05/2018 00:43:40
 *  Author: RodolfoSchiavi
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "def_inc.h"

#define DADOS_LCD PORTB //8 bits de dados do LCD na porta D
#define CONTR_LCD PORTD //os pinos de controle est?o no PORTB
#define RS PORTD2 //pino de instru??o ou dado para o LCD
#define E PORTD3 //pino de enable do LCD
#define pulso_enable() _delay_us(10); set_bit(CONTR_LCD,E); _delay_us(10); clr_bit(CONTR_LCD,E); _delay_us(450);

class LCD{
	public:
		void inic_LCD_8bits();
		void escreve_LCD(char*,bool);
		void cmd_LCD(unsigned char, char);
		void usuario_criado(unsigned char*);
	private:
		void sist_inic();
		void limpa();
	};



#endif /* LCD_H_ */