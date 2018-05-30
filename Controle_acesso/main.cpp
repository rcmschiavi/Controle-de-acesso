/*
 * Controle_acesso.cpp
 *
 * Created: 22/05/2018 21:24:29
 * Author : RodolfoSchiavi
 */ 


#include "def_inc.h"
#include "LCD.h"
#include "DB.h"

LCD lcd;
DB _db;
enum Estados {aguarda_digito,cod_especial,v_cod_dig,acessos,cria_user,permitido,negado};
enum Estados _estados;
unsigned char n_char_dig=0;
unsigned char cod_dig[10];

void inicializa_registradores();
void limpa_cod_dig();
void libera_entrada();

int main(void)
{
	inicializa_registradores();
	_estados=aguarda_digito;
	lcd.inic_LCD_8bits();
	lcd.tela_inicio();
	_db.cria_tabela();
    while(1){}
}

void inicializa_registradores(){
		DDRD |=0x0C;
		DDRB = 0XFF;
		DDRC |= (1<<LED);
		UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); //Ativa a interrupção por recebimento. A comunicação envio e recebimento
		UCSR0C = (1<<UPM01)|(1<<UCSZ00)|(1<<UCSZ01);
		UBRR0H = (BAUD_PRESCALE >> 8);
		UBRR0L = BAUD_PRESCALE;
		sei();
}
void processa_char(char c){
	if(c==0x0D){ //Verifica se foi pressionado o enter
		/*Preparar para enviar para verificação de senha*/
		//lcd.escreve_LCD("Enter",true);
		int res_senha =_db.verifica_senha(cod_dig,n_char_dig);
		if(res_senha==1){
			lcd.escreve_LCD("Bem-vindo!",true);
			libera_entrada();
		}
		else if(res_senha==2){
			/*Codigo para o código especial
			desnecessário no momento, pois tudo é feito no DB*/
		}
		else
			lcd.escreve_LCD("Acesso negado!",true);
		_delay_ms(1000);
		lcd.tela_inicio();
		limpa_cod_dig();
	}
	else if((c==0x08)&&(n_char_dig>0)){ //Verifica se o backspace foi pressionado e se o numero de caracteres é positivo
		n_char_dig--;
		cod_dig[n_char_dig]=0x00; //remove o ultimo caracter do array
		lcd.escreve_LCD("Senha: ",true);
		linha_inf;
		for(int i=0;i<n_char_dig;i++){
					lcd.escreve_LCD("*",false); //Escreve asteriscos para cada caracter na cod_dig
		}
	}
	else if(c>0x20){ //verifica se teclas não especiais foram pressionadas
		cod_dig[n_char_dig]=c;
		lcd.escreve_LCD("Senha: ",true);
		linha_inf;
		if(n_char_dig<9)
			n_char_dig++;
		for(int i=0;i<n_char_dig;i++){
			lcd.escreve_LCD("*",false);
		}
	}
}
void libera_entrada(){
	set_bit(PORTC,LED);
	_delay_ms(6000);
	clr_bit(PORTC,LED);
}
void limpa_cod_dig(){
	for(int i=0;i<n_char_dig;i++){
		cod_dig[i]=0x00;
	}
	n_char_dig=0;
}

ISR(USART_RX_vect){
	char ReceivedByte;
	ReceivedByte = UDR0; //Lê o registrador que tem a palavra recebida
	processa_char(ReceivedByte);
}