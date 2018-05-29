/*
 * Serial.cpp
 *
 * Created: 26/05/2018 01:35:19
 *  Author: RodolfoSchiavi
 */ 
#include "DB.h"

char DB::cod_esp[] = "*144#";

void DB::set_acesso(bool ok){
	acesso_permitido=ok;
}
void DB::cria_tabela(){
	n=1;
	db = (dataBase*) malloc(sizeof(dataBase)*n); //Cria um struct com tamanho dinâmico
	db[n-1].userID=n+48;
	for(int i=0;i<6;i++){
		db[n-1].senha[i]=i+49; //A senha do user 1 é 123456
	}
	db[n-1].acessos=48;
}
void DB::criar_user(){
	n++;
	db = (dataBase*) realloc(db,sizeof(dataBase)*n);
	db[n-1].userID=48+n;
	for(int i=0;i<6;i++){
		db[n-1].senha[i]=rand()%10+48; //Gera um número aleatório de 0 a 9 em decimal e convertido em char pela ascII
	}
	db[n-1].acessos=48;
	lcd.usuario_criado(&db[n-1].userID);
}

bool DB::verifica_senha(unsigned char *senha,unsigned char tamanho_senha){
	int caracteres_corretos=0;
 	if(tamanho_senha==6){
		 
		 for(int i=0;i<tamanho_senha;i++){
 			if(senha[i]==db[0].senha[i])
 				caracteres_corretos++;
		 }
 	}
	 if (caracteres_corretos==6)
		 return true;
	 else
		return false;
}