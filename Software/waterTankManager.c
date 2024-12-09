#include "waterTankManager.h"

virtualTimer timer_WTANK_timeout = 
{
  .targetTime = 15000,
  .elapsedTime  = 0,
  .active   = 0,
  .reached = 0
};

TankState tankState = WTANK_MID;
TankState lastTankState = WTANK_UNDEFINED;

void check_TankStatus(void)
{
  
  unsigned char top = pin_waterLevel_TOP;
  unsigned char bot = pin_waterLevel_BOT;
  
  if(tankState == WTANK_ERROR)
    tankState = WTANK_ERROR;
  
  //topo ativado e fundo desativado � fisicamente impossivel
  else if((top == 1 && bot == 0))
    tankState = WTANK_ERROR;
  
  //Se nao esta cheio e ainda tem agua no fundo
  else if(top == 0 && bot == 1)
    tankState = WTANK_MID;
  
  //Ambos os sensores ativados
  else if(top == 1 && bot == 1)
    tankState = WTANK_FULL;
  
  //Nenhum sensor ativado
  else if(top == 0 && bot == 0)
    tankState = WTANK_LOW;
  
  return;
}

void run_waterTankLogic(void)
{
    
  check_TankStatus();   
   
  switch (tankState)
  {
  case WTANK_ERROR: //Para de encher e aciona alarme
    stopFilling();
    pin_alarm = 0;
    break;
     
  case WTANK_LOW: //Comeca a encher e inicia o timeout
    startFilling();
    break;
    
  case WTANK_FULL: //Para de encher e para timeout
    stopFilling();
    break;
    
  case WTANK_MID: //Nada a fazer
    break;
    
  default: //Caso qualquer outra coisa aconte�a, eh um erro com certeza
    stopFilling();
    pin_alarm = 0;
  }; 
}

void startFilling(void) 
{
  pin_solenoid = 0; 
  startTimer(&timer_WTANK_timeout);
};
void stopFilling(void)  
{
  pin_solenoid = 1; 
  stopTimer(&timer_WTANK_timeout);
};

/**
 * Boa pratica ter uma funcao exclusiva para interrupcao
 * Caso chamar uma funcao que altera uma variavel global(sem reentrancia), seja usada tanto na main quanto em uma interrupcao, o compilador xc8 duplica a funcao(talvez por medo de acontecer multipla )
 * saiba mais em: https://cwe.mitre.org/data/definitions/479.html#:~:text=Non-reentrant%20functions%20are%20functions,without%20resulting%20in%20memory%20corruption.
*/
