#include "irrigation.h"

virtualTimer timer_IRRIG_Timeout = 
{
  .targetTime = 20,
  .callback = interrupt_IRRIG_timeout
};

IrrigationState irrigationState = IRRIG_OFF;
IrrigationState lastIrrigationState = IRRIG_UNDEFINED;

unsigned char minHumidity = 30;
unsigned char idealHumidity = 50;
__bit isIrrigating = 0;

//Executa a logica para irrigar, caso passe todas as checagens e a humidade esteja baixa, irrigue
void run_IrrigationLogic(int sMoistureValue)
{
  
  if(irrigationState == IRRIG_ERROR) //Erro de timeoout
  {
    stopIrrigation();
//    pin_alarm = 0; //Liga alarme
  }
  
  else if(tankState == WTANK_LOW || tankState == WTANK_ERROR) //Caso Tanque de agua esteja vazio ou com erro
  stopIrrigation();
    
  else if(sMoistureValue <= minHumidity) //Se umidade esta abaixo, liga
    startIrrigation();
  
  else if(sMoistureValue >= idealHumidity) //Se chegou na umidade ideal, desliga
    stopIrrigation();
}

void startIrrigation()
{
  if(isIrrigating)
    return;
  
  pin_waterPump = 0;
  irrigationState = IRRIG_ON;
  isIrrigating = 1;
  startTimer(&timer_IRRIG_Timeout);
}

void stopIrrigation()
{
  if(!isIrrigating)
    return;
  
  pin_waterPump = 1;
  isIrrigating = 0;
  irrigationState = IRRIG_OFF;
  stopTimer(&timer_IRRIG_Timeout);
}

void interrupt_IRRIG_timeout(void)
{
  stopIrrigation();
  irrigationState = IRRIG_ERROR;
}