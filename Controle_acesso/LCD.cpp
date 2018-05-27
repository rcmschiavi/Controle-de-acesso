/*
 * LCD.cpp
 *
 * Created: 26/05/2018 00:43:51
 *  Author: RodolfoSchiavi
 */ 
#include "LCD.h"

void LCD::inic_LCD_8bits()//sequ?ncia ditada pelo fabricando do circuito de controle do LCD
{
	clr_bit(CONTR_LCD,RS);//o LCD ser? s? escrito ent?o R/W ? sempre zero
	_delay_ms(15); //tempo para estabilizar a tens?o do LCD, ap?s VCC ultrapassar 4.5 V (pode ser bem maior na pr?tica)//
	DADOS_LCD = 0x38; //interface 8 bits, 2 linhas, matriz 7x5 pontos
	pulso_enable(); //enable respeitando os tempos de resposta do LCD
	_delay_ms(5);
	pulso_enable();
	_delay_us(200);
	pulso_enable();
	pulso_enable();
	//cmd_LCD(0X0E,0);
	cmd_LCD(0x08,0); //desliga LCD
	cmd_LCD(0x01,0); //limpa todo o display
	cmd_LCD(0x0C,0); //mensagem aparente cursor inativo n?o piscando
	cmd_LCD(0x80,0); //escreve na primeira posi??o a esquerda - 1? linha
	sist_inic();
}
void LCD::cmd_LCD(unsigned char c, char cd)//c ? o dado e cd indica se ? instru??o ou caractere
{
	DADOS_LCD = c;
	if(cd==0)
	clr_bit(CONTR_LCD,RS); //RS = 0
	else
	set_bit(CONTR_LCD,RS); //RS = 1
	pulso_enable();	//se for instru??o de limpeza ou retorno de cursor espera o tempo necess?rio
	if((cd==0) && (c<4))
	_delay_ms(2);
}
void LCD::escreve_LCD(char *c,bool limpar)
{
	if(limpar)	limpa();
	for (; *c!=0;c++) cmd_LCD(*c,1);
}
void LCD::limpa()
{
	cmd_LCD(0x01,0);
}
void LCD::sist_inic(){
	escreve_LCD("Sistema iniciado.",true);
	_delay_ms(500);
	limpa();
}
void LCD::usuario_criado(unsigned char* usuario){
	limpa();
	cmd_LCD(0x80,0); //Seta o cursor pra primeira posição
	escreve_LCD("UserID: ",false);
	cmd_LCD(*usuario,1);
	cmd_LCD(0x80|0x40,0); //Seta o cursor pra linha de baixo
	escreve_LCD("Senha: ",false);											   
	for(int i=0;i<6;i++){
		usuario++;
		cmd_LCD(*usuario,1);
	}
	_delay_ms(5000);
}