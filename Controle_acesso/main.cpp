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
unsigned char senha[10];

void inicializa_registradores();
void limpa_senha();

int main(void)
{
	inicializa_registradores();
	_estados=aguarda_digito;
	lcd.inic_LCD_8bits();
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
		lcd.escreve_LCD("Enter",true);
		if(_db.verifica_senha(senha,n_chars_senha)){
			lcd.escreve_LCD("Belezaa",true);
		}
		else
			lcd.escreve_LCD("Não deu match!",true);
		_delay_ms(500);
		lcd.escreve_LCD("Digite a senha:",true);
		limpa_senha();
	}
	else if((c==0x08)&&(n_chars_senha>0)){ //Verifica se o backspace foi pressionado e se o numero de caracteres é positivo
		n_chars_senha--;
		senha[n_chars_senha]=0x00; //remove o ultimo caracter do array
		lcd.escreve_LCD("Senha: ",true);
		for(int i=0;i<n_chars_senha;i++){
					lcd.escreve_LCD("*",false); //Escreve asteriscos para cada caracter na senha
		}
	}
	else if(c>0x21){ //verifica se teclas não especiais foram pressionadas
		senha[n_chars_senha]=c;
		lcd.escreve_LCD("Senha: ",true);
		if(n_chars_senha<9)
			n_chars_senha++;
		for(int i=0;i<n_chars_senha;i++){
			lcd.escreve_LCD("*",false);
		}
	}
}
void limpa_senha(){
			for(int i=0;i<n_chars_senha;i++){
				senha[i]=0x00;
			}
			n_chars_senha=0;
}

ISR(USART_RX_vect){
	char ReceivedByte;
	ReceivedByte = UDR0; //Lê o registrador que tem a palavra recebida
	processa_char(ReceivedByte);
}