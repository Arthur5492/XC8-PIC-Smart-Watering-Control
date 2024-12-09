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

void __interrupt() interruptionHandler(void)
{
  if(INTCONbits.INTF) //RB0 
  {
    INTCONbits.INTF = 0;
    tankState = WTANK_MID;
  }
  else if(PIR1bits.TMR1IF)//Timer 1
  {
    PIR1bits.TMR1IF = 0;
    
    setCounter_Timer1();
    
    runTimer(&timer_WTANK_timeout);
    runTimer(&timer_lcdButtons);
  }
}

void main()
{
  ///OUTPUT SETUP
  pin_solenoid        = 1; //Acionados em LOW
  pin_waterPump       = 1; 
  pin_airConditioner  = 1;
  pin_alarm           = 1;
  pin_artificialLight = 0;
  //END OUTPUT SETUP
  
  //       {TRISA,TRISB,TRISC,TRISD}
  pins_init(0xFF ,0xFF ,0x00 ,0x00);
  interruption_init();
  timer1_1ms_init();
  Lcd_Init();
  print_Index();
  
  while(1)
  {
    CLRWDT();
    
    run_waterTankLogic();
    lcd_run();

      
  }
  
  return;
}