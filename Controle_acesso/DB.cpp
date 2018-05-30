/*
 * Serial.cpp
 *
 * Created: 26/05/2018 01:35:19
 *  Author: RodolfoSchiavi
 */ 
#include "DB.h"


void DB::set_acesso(bool ok){
	acesso_permitido=ok;
}
void DB::cria_tabela(){
	n=1;
	db = (dataBase*) malloc(sizeof(dataBase)*n); //Cria um struct com tamanho dinâmico
	db[n-1].userID=n;
	for(int i=0;i<6;i++){
		db[n-1].senha[i]=i+49; //A senha do user 1 é 123456
	}
	db[n-1].acessos=0;
}
void DB::criar_user(){
	n++;
	db = (dataBase*) realloc(db,sizeof(dataBase)*n);
	db[n-1].userID=n;
	for(int i=0;i<6;i++){
		db[n-1].senha[i]=rand()%9+48; //Gera um número aleatório de 0 a 9 em decimal e convertido em char pela ascII
	}
	db[n-1].acessos=0;
	lcd.usuario_criado(&db[n-1].userID);
}

int DB::verifica_senha(unsigned char *senha,unsigned char tamanho_senha){
	int caracteres_corretos=0;
 	if(tamanho_senha==6){
		 for(int i=0;i<n;i++){
			 caracteres_corretos =0;
			 for(int j=0;j<tamanho_senha;j++){
 				if(senha[j]==db[i].senha[j]){
 					caracteres_corretos++;
					if (caracteres_corretos==tamanho_senha){
						db[i].acessos++;
					 	 return 1;
					}
				 }
			 }
		 }
 	}
	else if(tamanho_senha==5){
		for(int i=0;i<2;i++){
			caracteres_corretos=0;
			for(int j=0;j<tamanho_senha;j++){
				if(senha[j]==cod_esp[i][j]){
					caracteres_corretos++;
					if(caracteres_corretos==tamanho_senha){
						opera_cod(i);
						return 2;
					}
				}
			}
		}
	}
	return 0;
}

void DB::opera_cod(int op){
	if(op==0){ //Verifica se o código especial se refere ao número de acessos
		int n_acessos=0;
		char str[16];
		for (int i=0;i<n;i++)
		{
			n_acessos += db[i].acessos;
		}
		itoa(n_acessos, str,10); //Tratamento do valor do inteiro para quando passar de 9 não seguir a tabela ascII
		lcd.escreve_LCD("N acessos: ",true);
		linha_inf;
		lcd.escreve_LCD(str,false);
		_delay_ms(500);
	}
	else if(op==1){ //Verifica se é para criar outro usuário
		criar_user();
	}
}