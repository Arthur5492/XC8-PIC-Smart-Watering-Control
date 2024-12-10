#include "irrigation.h"

virtualTimer timer_IRRIG_Timeout = 
{
  .targetTime = 20,
  .elapsedTime = 0,
  .active = 0,
  .callback = interrupt_IRRIG_timeout
};

IrrigationState irrigationState = IRRIG_OFF;
IrrigationState lastIrrigationState = IRRIG_UNDEFINED;

unsigned char minHumidity = 30;
unsigned char idealHumidity = 50;
__bit isIrrigating = 0;

void run_IrrigationLogic(int sMoistureValue)
{
  if(tankState == WTANK_LOW || tankState == WTANK_ERROR)
    stopIrrigation();
  
  else if(irrigationState == IRRIG_ERROR)
    stopIrrigation();
  
  else if(sMoistureValue <= minHumidity)
    startIrrigation();
  
  else if(sMoistureValue >= idealHumidity)
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