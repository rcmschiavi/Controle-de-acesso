/*
 * Serial.h
 *
 *Arquivo de cabe�alho para a classa DB - Data Base que cont�m os dados dos usu�rios, fazendo a inclus�o e verifica��o dos c�digos inseridos
 *
 * Created: 26/05/2018 01:35:28
 *  Author: RodolfoSchiavi
 */ 


#ifndef DB_H_
#define DB_H_
#include "def_inc.h"
#include "LCD.h"

class DB{
	public:
		void set_acesso(bool ok);
		bool get_acesso(){ return acesso_permitido; }
		void cria_tabela();
		int verifica_senha(unsigned char*,unsigned char);
	private:
	LCD lcd;
		void criar_user();
		void opera_cod(int);
		struct dataBase{
			unsigned char userID, senha[6], acessos;
		};
		int n;
		dataBase *db;
		bool acesso_permitido;
		unsigned char cod_esp[2][6] = {"*144#","!122@"};
	};



#endif /* SERIAL_H_ */