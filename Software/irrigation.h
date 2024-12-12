#ifndef IRRIGATION_H
#define IRRIGATION_H

#include "pins.h"
#include "virtualTimer.h"
#include "waterTankManager.h"

typedef enum
{
  IRRIG_UNDEFINED = -1,
  IRRIG_ON,
  IRRIG_OFF,
  IRRIG_ERROR
}IrrigationState;

extern IrrigationState irrigationState;
extern IrrigationState lastIrrigationState;

extern virtualTimer timer_IRRIG_Timeout;

//PARAMETERS
extern unsigned char minHumidity; //Caso chegue nesse valor, irrigacao precisa ser feita
extern unsigned char idealHumidity; //Umidade ideal
extern __bit isIrrigating;
//


void run_IrrigationLogic(int soilMoistureValue);
void interrupt_IRRIG_timeout(void);

void startIrrigation(void);
void stopIrrigation(void);

#endif