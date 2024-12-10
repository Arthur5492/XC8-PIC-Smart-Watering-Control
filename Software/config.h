/**
 * @file config.h
 * @brief Configura definicoes e inicializacoes gerais do microcontrolador.
 * @details Inclui configuracoes de clock, ADC, timers, pinos e interrupcoes.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <xc.h>
#include <stdio.h>

#define SBIT_ADON     0
#define SBIT_CHS0     3
#define SBIT_ADFM     7

//CRYSTAL FREQ
#define _XTAL_FREQ 4000000

#pragma config FOSC = HS        // Oscillator Selection bits 
#pragma config WDTE = ON        // Watchdog Timer Enable bit 
#pragma config PWRTE = ON       // Power-up Timer Enable bit (reset ao ligar))
#pragma config BOREN = ON       // Brown-out Reset Enable bit (reset quando houverem quedas abruptas na fonte de energia) 
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

//GLOBAL VARIABLES
int soilMoisture = 0;
int temperature = 0;
int light = 0;

int old_soilMoisture = -1;
int old_temperature = -1;
int old_light = -1;
//END GLOBAL VARIABLES

void    WDT_init() // 8 bits, 18 - 2304 ms
{
  OPTION_REGbits.PSA = 1;  //0: Timer0 / 1:WDT

  //Pre Scaler 8bits 1:1 to 1:128, period: 18ms
  OPTION_REGbits.PS0 = 1;
  OPTION_REGbits.PS1 = 1;
  OPTION_REGbits.PS2 = 1;

  CLRWDT();  
}

void timer1_1ms_init(void) //16 bits 
{ 
  T1CONbits.TMR1CS = 0;   //Clock Source -> 0: Internal Clk / 1: External clk

  //Pre Scaler 2 bits 1:1 to 1:8 -> max time = 8us*65535 = 0,524s 
  T1CONbits.T1CKPS0 = 1;  
  T1CONbits.T1CKPS1 = 1;  

  // 1000us/8us = 125, thus, start timer value at 65536 - 125 = 65411, so starts at 65411
//  TMR1H = 0xFF; //Most significative
//  TMR1L = 0x83; //Less significative  
  
  TMR1L = 0xDC;          //carga do valor inicial no contador (65536-62500)
  TMR1H = 0x0B;          //3036. Quando estourar contou 62500, passou 0,5s
  
  T1CONbits.TMR1ON = 1;   //turn on timer
}



////Learn more in; https://www.microcontrollerboard.com/pic-timer2-tutorial.html
//void timer2_500ms_init() //16 bits 
//{ 
//  //Pre scaler 2 bits; 00 = 1:1 / 01 = 1:4 / 1x = 1:16
//  T2CONbits.T2CKPS0 = 1; 
//  T2CONbits.T2CKPS1 = 1;
//  
//  //Post Scale 4 bits 1:1 to 1:16 
//  T2CONbits.TOUTPS0 = 1;
//  T2CONbits.TOUTPS1 = 1;
//  T2CONbits.TOUTPS2 = 1;
//  T2CONbits.TOUTPS3 = 1;
//  
//  //8 bit register for TMR2 initial value iterator
//  TMR2 = 0x00; 
//  //8 bit register for TMR2 last value iterator
//  PR2 = 0xFF;
//}

void pins_init(unsigned char _TRISA, unsigned char _TRISB, unsigned char _TRISC, unsigned char _TRISD) {
  TRISA = _TRISA;   
  TRISB = _TRISB;   
  TRISC = _TRISC;
  TRISD = _TRISD;

  OPTION_REGbits.nRBPU = 0; // 0: enable pull up PORTB / 1: Disable pull up PORTB:

  TRISCbits.TRISC6 = 1; //sensores de nivel de agua
  TRISCbits.TRISC7 = 1;
}

void interruption_init(void)
{
  INTCONbits.GIE=1;           //int global
  OPTION_REGbits.INTEDG = 1;  // 0: negedge 1:posedge
  
  INTCONbits.INTE = 1;        //int extern from rb0
  
  INTCONbits.PEIE = 1;        //int Perifericals 
  
  PIE1bits.TMR1IE = 1;        //int timer1
};

void ADC_init() {
   //define as entradas como analogicas
   ADCON1bits.PCFG0=0;
   ADCON1bits.PCFG1=0;
   ADCON1bits.PCFG2=0;
   ADCON1bits.PCFG3=0;

   //10 bits
   ADCON1bits.ADFM = 1;
   
   //define o clock de conversao
   ADCON0bits.ADCS0 = 0  ;   //confirmando default Fosc/2
   ADCON0bits.ADCS1 = 0  ;   //confirmando default Fosc/2
   
   ADCON0bits.ADON = 1;
}

int ADC_Read(unsigned char channel) {
  
  // Seleciona o canal
  ADCON0bits.CHS = channel;
    
  // Aguarda o tempo de aquisicao para carregar o capacitor
  __delay_us(20);

  while (ADCON0bits.nDONE) {}; /* wait for any previous conversion to finish */
  
  // Inicia a conversao A/D
  ADCON0bits.GO = 1;
  // Aguarda ate que a conversao seja concluida
  while (ADCON0bits.nDONE)
    {};

  return((ADRESH<<8) + ADRESL); //return right justified 10-bit result
}

// Funcao map sem acentos nos comentarios
long map(int x, int in_min, int in_max, int out_min, int out_max) {
    // Declarar variaveis locais evita conflitos
    long run = (long)in_max - (long)in_min;
    
    if (run == 0) // Se in_max == in_min, evita divisao por zero retornando out_min
        return out_min;
    
    long rise = (long)out_max - (long)out_min;
    long delta = (long)x - (long)in_min;
    // Multiplicacao e divisao em long para evitar overflow
    return (delta * rise) / run + out_min;
}

void readSoilMoisture(void)
{
  soilMoisture = ADC_Read(0);
  soilMoisture = (int)map(soilMoisture,0,1023,0,100);
}

/*Sensor de temperatura - LM35 - usando de 0ºC a 150ºC
* PIC Recebe tensao em V, 0V a 1.5V pois o LM35 a cada 1ºC aumenta 0.01V 0.01V * 150ºC = 1.5V
* variavel recebe valor  de 0-1023
* Convertendo novamente para V para deduzir a temperatura e entao
* multiplicar (temperature*100) ex: 0.05V*100 = 5ºC
*/
void readTemperature(void)
{
  temperature = ADC_Read(1);
  temperature = (int)map(temperature,0,1023,0,500);
}

void readLight(void)
{
  light = ADC_Read(2);
}

void ADC_readAll(void)
{
  readTemperature();
  readSoilMoisture();
  readLight();
}
#endif