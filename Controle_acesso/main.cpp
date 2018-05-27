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
enum Estados {aguarda_digito,cod_especial,v_senha,acessos,cria_user,permitido,negado};
enum Estados _estados;
unsigned char n_chars_senha=0;
unsigned char n_chars_cod=0;
char senha[6];
char codigo[5];

void inicializa_registradores();
void verifica_cod();
void verifica_senha();

int main(void)
{
	inicializa_registradores();
	_estados=aguarda_digito;
	lcd.inic_LCD_8bits();
	_db.cria_tabela();
    while (1){}
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
	if(c=='*'){
		/*código para caracteres especiais*/
		if (_estados==aguarda_digito){
			codigo[0]=c;
			n_chars_cod=1;
			_estados=cod_especial;
		}
		else{
			/*Erro, não é possível digitar esse caracter durante outros estados*/
		}
	}
	else if(c==0x08){ //Verifica se a tecla é backspace
		if(_estados!=aguarda_digito){
			lcd.cmd_LCD(0b010000,0); //Seta o cursor pra uma casa antes
			_delay_ms(10);
			lcd.cmd_LCD(0b00100000,1); //Substitui o caracter por espaço
			lcd.cmd_LCD(0b010000,0); //Volta uma casa
			clp_bit(PORTC,LED);
			if(_estados==v_senha)
			n_chars_senha--;
			else if(_estados==cod_especial)
			n_chars_cod--;
		}
	}
	else if((c>48)&&(c<57)){
		if((_estados==aguarda_digito)||(_estados==v_senha)){
			senha[n_chars_senha]=c;
			n_chars_senha++;
		}
		else if(_estados==cod_especial){
			n_chars_cod++;
			codigo[n_chars_cod-1]=c;
		}
	}
	else{
		lcd.escreve_LCD("Caracter inválido!",true);
		_delay_ms(1000);
	}
	if(n_chars_cod==5){
		verifica_cod();
		n_chars_cod=0;
	}
	else if(n_chars_senha==6){
		verifica_senha();
		n_chars_senha=0;
	}
		
}

void verifica_cod(){
	lcd.cmd_LCD(0x80,0);
	lcd.escreve_LCD("Codigo especial: ",true);
	lcd.cmd_LCD(0x40|0x80,0);
	lcd.escreve_LCD(codigo,false);
}

void verifica_senha(){
	
}

ISR(USART_RX_vect){
	char ReceivedByte;
	ReceivedByte = UDR0; //Lê o registrador que tem a palavra recebida
	processa_char(ReceivedByte);
}