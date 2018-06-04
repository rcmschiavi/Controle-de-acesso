/*
 * LCD.h
 *
 *Arquivo de cabeçalho da classe LCD que faz as atividades mais internas do display
 *
 * Created: 26/05/2018 00:43:40
 *  Author: RodolfoSchiavi
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "def_inc.h"


class LCD{
	public:
		void inic_LCD_8bits();
		void escreve_LCD(char*,bool);
		void cmd_LCD(unsigned char, char);
		void usuario_criado(unsigned char*);
		void tela_inicio();
		void cria_caracter();
	private:
		void sist_inic();
		void limpa();
	};



#endif /* LCD_H_ */