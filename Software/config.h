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

<<<<<<< HEAD
void ADC_init() {
   //define as entradas como analogicas
   ADCON1bits.PCFG0=0;
   ADCON1bits.PCFG1=0;
   ADCON1bits.PCFG2=1;
   ADCON1bits.PCFG3=1;

   //10 bits
   ADCON1bits.ADFM = 1;

   //define o clock de conversao
   ADCON0bits.ADCS0 = 0  ;   //confirmando default Fosc/2
   ADCON0bits.ADCS1 = 0  ;   //confirmando default Fosc/2
}

int ADC_Read(unsigned char channel) {
    // Seleciona o canal
    ADCON0bits.CHS = channel;

    // Aguarda o tempo de aquisicao para carregar o capacitor
    __delay_us(20);

    // Inicia a conversao A/D
    GO_nDONE = 1;

    // Aguarda ate que a conversao seja concluida
    while (GO_nDONE);

    // Retorna o resultado da conversao (10 bits)
    return ((ADRESH << 8) + ADRESL);
}

void    WDT_init() // 8 bits, 18 - 2304 ms
{
  OPTION_REGbits.PSA = 1;  //0: Timer0 / 1:WDT

  //Pre Scaler 8bits 1:1 to 1:128, period: 18ms
  OPTION_REGbits.PS0 = 1;
  OPTION_REGbits.PS1 = 1;
  OPTION_REGbits.PS2 = 1;

  CLRWDT();  
=======
//void ADC_init() {
//   //define todas as entradas como analogicas
//   ADCON1bits.PCFG0=0;
//   ADCON1bits.PCFG1=0;
//   ADCON1bits.PCFG2=0;
//   ADCON1bits.PCFG3=0;
//
//   //10 bits
//   ADCON1bits.ADFM = 1;
//
//   //define o clock de conversao
//   ADCON0bits.ADCS0 = 0  ;   //confirmando default Fosc/2
//   ADCON0bits.ADCS1 = 0  ;   //confirmando default Fosc/2
//}
//
//int ADC_read(unsigned char adcChannel){   
//    ADCON0bits.ADON=1;
//
//    //inicializar valor analogico com 0
//    ADRESL = 0x00;          
//    ADRESH = 0x00; 
//
//    ADCON0bits.CHS0=adcChannel;
//    ADCON0bits.CHS1=0;
//    ADCON0bits.CHS2=0;
//
//    __delay_ms(1000); //Acquisition Time(Wait for Charge Hold Capacitor to get charged )
//
//    ADCON0bits.GO=1;
//    __delay_us(10);
//    return((ADRESH<<8) + ADRESL); //return right justified 10-bit result
//}
//
//void    WDT_init() // 8 bits, 18 - 2304 ms
//{
//  OPTION_REGbits.PSA = 1;  //0: Timer0 / 1:WDT
//
//  //Pre Scaler 8bits 1:1 to 1:128, period: 18ms
//  OPTION_REGbits.PS0 = 1;
//  OPTION_REGbits.PS1 = 1;
//  OPTION_REGbits.PS2 = 1;
//
//  CLRWDT();  
//}

void setCounter_Timer1()
{
  // 1000us/8us = 125, thus, start timer value at 65535 - 125 = 65383, so starts at 65383
  TMR1H = 0xFF; //Most significative
  TMR1L = 0x67; //Less significativ
>>>>>>> 9f36d0eeb2a1ed5450943b6f6b10d4eba599b5d5
}

void timer1_1ms_init(void) //16 bits 
{ 
  T1CONbits.TMR1CS = 0;   //Clock Source -> 0: Internal Clk / 1: External clk

  //Pre Scaler 2 bits 1:1 to 1:8 -> max time = 8us*65535 = 0,524s 
  T1CONbits.T1CKPS0 = 1;  
  T1CONbits.T1CKPS1 = 1;  

<<<<<<< HEAD
  // 1000us/8us = 125, thus, start timer value at 65536 - 125 = 65411, so starts at 65411
  TMR1H = 0xFF; //Most significative
  TMR1L = 0x83; //Less significative  
=======
  setCounter_Timer1();   
>>>>>>> 9f36d0eeb2a1ed5450943b6f6b10d4eba599b5d5
  
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

<<<<<<< HEAD
  TRISCbits.TRISC6 = 1; //sensores de nivel de agua
  TRISCbits.TRISC7 = 1;
=======
>>>>>>> 9f36d0eeb2a1ed5450943b6f6b10d4eba599b5d5
}

void interruption_init(void)
{
  INTCONbits.GIE=1;           //int global
  OPTION_REGbits.INTEDG = 1;  // 0: negedge 1:posedge
  
  INTCONbits.INTE = 1;        //int extern from rb0
  
  INTCONbits.PEIE = 1;        //int Perifericals 
  
  PIE1bits.TMR1IE = 1;        //int timer1
}



#endif