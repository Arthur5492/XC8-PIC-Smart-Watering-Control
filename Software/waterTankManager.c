#include "waterTankManager.h"

virtualTimer timer_WTANK_Timeout = 
{
  .targetTime = 30,
  .callback = interrupt_WTANK_timeout
};

TankState tankState = WTANK_MID;
TankState lastTankState = WTANK_UNDEFINED;
__bit isFilling = 0;

//Verifica com base nos sensores de nivel de agua o status do tanque de agua
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

//Executa a logica de enchimento de tanque baseado no estado atual do tanque
void run_waterTankLogic(void)
{
    
  check_TankStatus();   
   
  switch (tankState)
  {
  case WTANK_ERROR: //Para de encher e aciona alarme
    stopFilling();
//    pin_alarm = 0;
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
  }; 
}

//Liga solenoide
void startFilling(void) 
{
  if(isFilling)
    return;
  
  isFilling = 1;
  pin_solenoid = 0; 
  startTimer(&timer_WTANK_Timeout);
};

//Desliga solenoide
void stopFilling(void)  
{
  if(!isFilling)
    return;
  
  isFilling = 0;
  pin_solenoid = 1; 
  stopTimer(&timer_WTANK_Timeout);
};

/** Nao estou mais executando essa funcao no ISR, mas quando estava aprendi sobre isso:
 * Boa pratica ter uma funcao exclusiva para interrupcao pois
 * caso uma funcao que altera uma variavel global(sem reentrancia), seja usada na main E na interrupcao, o compilador xc8 duplica a funcao e da warning
 * saiba mais em: https://cwe.mitre.org/data/definitions/479.html#:~:text=Non-reentrant%20functions%20are%20functions,without%20resulting%20in%20memory%20corruption.
 * 
 * Agora ela eh executada no loop pelo seu respectivo virtualTimer
*/
void interrupt_WTANK_timeout(void)
{
  stopFilling();
  tankState = WTANK_ERROR;
}
