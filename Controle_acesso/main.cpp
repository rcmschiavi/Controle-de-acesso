/*
 * Controle_acesso.cpp
 *
 *Projeto de controle de acesso do laborat�rio
 *
 *
 *
 * Created: 22/05/2018 21:24:29
 * Author : RodolfoSchiavi
 */ 


#include "def_inc.h"
#include "LCD.h"
#include "DB.h"

LCD lcd;
DB _db;
unsigned char n_char_dig=0;
unsigned char cod_dig[10];

/*Cabe�alho de fun��es*/
void inicializa_registradores();
void limpa_cod_dig();
void libera_entrada();

int main(void)
{
	inicializa_registradores();
	lcd.inic_LCD_8bits(); //Inicializa os display
	lcd.tela_inicio();	//Fun��o de tela de inicio
	_db.cria_tabela();	//cria a tabela como o usu�rio 1
    while(1){}
}

void inicializa_registradores(){
	/*Fun��o para inicializar os registradores de forma mais organizada*/
		DDRD |= (1<<PORTD2)|(1<<PORTD3); //modifica somente como saida as portas de comando do display 
		DDRB = 0XFF; //Seta as portas de dados do lcd como sa�da
		DDRC = (1<<LED); //Seta a porta do led como saida
		UCSR0B = (1<<RXCIE0)|(1<<RXEN0); //Ativa a interrup��o por recebimento. A comunica��o envio e recebimento
		UCSR0C = (1<<UPM01)|(1<<UCSZ00)|(1<<UCSZ01); //	Habilita a paridade par, e 8 bits de comunica��o
		UBRR0H = (BAUD_PRESCALE >> 8); //Seta os bits mais significativos do UBRR0
		UBRR0L = BAUD_PRESCALE; //Seta os bits menos significativos do UBRR0
		sei(); //Ativa as interrup��es globais
}
void processa_char(char c){
	if(c==0x0D){ //Verifica se foi pressionado o enter
		/*Preparar para enviar para verifica��o de senha*/
		int res_senha =_db.verifica_senha(cod_dig,n_char_dig);
		if(res_senha>0){
			char str[16];
			itoa(res_senha, str,10);
			lcd.escreve_LCD("Bem-vindo, ",true);
			lcd.escreve_LCD(str,false);
			lcd.escreve_LCD("!",false);
			libera_entrada();
		}
		else if(res_senha==-1){
			/*Codigo para o c�digo especial
			desnecess�rio no momento, pois tudo � feito no DB*/
		}
		else
			lcd.escreve_LCD("Acesso negado!",true);
		_delay_ms(1000);
		lcd.tela_inicio();
		limpa_cod_dig();
	}
	else if((c==0x08)&&(n_char_dig>0)){ //Verifica se o backspace foi pressionado e se o numero de caracteres � positivo
		n_char_dig--;
		cod_dig[n_char_dig]=0x00; //remove o ultimo caracter do array
		lcd.escreve_LCD("Senha: (Enter)",true);
		linha_inf;
		for(int i=0;i<n_char_dig;i++){
					lcd.escreve_LCD("*",false); //Escreve asteriscos para cada caracter na cod_dig
		}
	}
	else if(c>0x20){ //verifica se teclas n�o especiais foram pressionadas
		cod_dig[n_char_dig]=c;
		lcd.escreve_LCD("Senha: (Enter)",true);
		linha_inf;
		if(n_char_dig<9) //Verifica se n�o foi digitado mais de 9 caracteres, limitando a escrita
			n_char_dig++;
		for(int i=0;i<n_char_dig;i++){
			lcd.escreve_LCD("*",false); //Escreve um aster�sco no lugar da senha, por seguran�a
		}
	}
}
void libera_entrada(){
	/*Fun��o que libera a entrada*/
	set_bit(PORTC,LED);
	_delay_ms(6000);
	clr_bit(PORTC,LED);
}
void limpa_cod_dig(){
	/*Fun��o que limpa o que foi digitado*/
	for(int i=0;i<n_char_dig;i++){
		cod_dig[i]=0x00;
	}
	n_char_dig=0;
}

ISR(USART_RX_vect){
	/*Fun��o de interrup��o da serial*/
	char ReceivedByte;
	ReceivedByte = UDR0; //L� o registrador que tem a palavra recebida
	processa_char(ReceivedByte);
}