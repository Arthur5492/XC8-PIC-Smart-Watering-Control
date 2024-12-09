/*
 * @file main.c
 *
 * 
 *
 */

#include "config.h"
#include "pins.h"
#include "lcdFunctions.h"
#include "virtualTimer.h"
#include "waterTankManager.h"

#include "irrigation.h"

void __interrupt() interruptionHandler(void)
{
  if(INTCONbits.INTF) //RB0 
  {
    INTCONbits.INTF = 0;
    tankState = WTANK_ERROR;
    irrigationState = IRRIG_ERROR;
  }
  else if(PIR1bits.TMR1IF)//Timer 1
  {
    PIR1bits.TMR1IF = 0;
    
//    Reseta timer ao valor desejado
    TMR1H = 0xFF; //Most significative
    TMR1L = 0x67; //Less significative 
    
    runTimer(&timer_WTANK_timeout);
    runTimer(&timer_lcdButtons);
  }
}

void main()
{
  ///INICIALIZACAO
  //Acionados em LOW
  pin_solenoid        = 1; 
  pin_waterPump       = 1; 
  pin_airConditioner  = 1;
  pin_alarm           = 1;
  //
  pin_artificialLight = 0;
  //END INICIALIZACAO
  
  //       {TRISA,TRISB,TRISC,TRISD}
  pins_init(0xFF ,0xFF ,0x00 ,0x00);
  WDT_init();
  interruption_init();
  timer1_1ms_init();
  ADC_init();
  Lcd_Init();
  
  while(1)
  {
    CLRWDT();
    
    run_waterTankLogic();
    lcd_run();
    
  }
  
  return;
}