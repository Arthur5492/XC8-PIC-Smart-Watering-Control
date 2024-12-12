/*
 * @file main.c
 *
 * 
 *
 */

#include "config.h"
#include "pins.h"
#include "lcdFunctions.h"
#include "analogValues.h"

#include "virtualTimer.h"

#include "waterTankManager.h"
#include "irrigation.h" 

//Virtual Timer, saiba mais acessando "virtualTimer.h"
virtualTimer timer_ADCReadAll =
{
  .targetTime = 2,
  .callback = ADC_readAll
};

void __interrupt() interruptionHandler(void)
{
  if(INTCONbits.INTF) //Testanado flag int RB0
  {
    INTCONbits.INTF = 0;
    tankState = WTANK_ERROR;
    irrigationState = IRRIG_ERROR;
  }
  else if(PIR1bits.TMR1IF)// 0,5s Interrupcao de timer 1
  {
    PIR1bits.TMR1IF = 0;
    
    //0,5s - reseta registradores do timer1 para valor desejado
    TMR1L = 0xDC;          //carga do valor inicial no contador (65536-62500)
    TMR1H = 0x0B;          //3036. Quando estourar, contou 62500, passou 0,5s
    
    timerCounter++; //Counter que todos os virtualTimers verificam
  }
}

void main()
{
  //       {TRISA,TRISB,TRISC,TRISD}
  pins_init(0xFF ,0xFF ,0x00 ,0x00);
  
  ///INICIALIZACAO
  //Acionados em LOW
  pin_solenoid        = 1; 
  pin_waterPump       = 1; 
  pin_airConditioner  = 1;
  pin_alarm           = 1;
  //
  pin_artificialLight = 1;
  //END INICIALIZACAO
  
  
  WDT_init();
  interruption_init();
  timer1_1ms_init();
  ADC_init();
  Lcd_Init();
  
  //Ler Sensores Analogicos antes de entrar no loop(pois ADC_readAll so eh executado no loop apos 1s por estar em um virtualTimer)
  ADC_readAll();
  
  startTimer(&timer_ADCReadAll);
  
  while(1)
  {
    CLRWDT();    
    run_waterTankLogic();
    run_IrrigationLogic(soilMoisture);
    lcd_run();
    
    //timers rodando constatemente e executando suas funcoes de callback quando chegam no tempo definido
    runTimer(&timer_WTANK_Timeout);
    runTimer(&timer_IRRIG_Timeout);
    runTimer(&timer_ADCReadAll);
    
    
    //Logicas simples
    if(light >= 900) //Valor ADC que indica baixa luz
      pin_artificialLight = 0;
    else
      pin_artificialLight = 1;
    
    if(temperature >= 30) //graus Celsius
      pin_airConditioner = 0;
    else
      pin_airConditioner = 1;
  }
  
  return;
}