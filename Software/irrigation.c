#include "irrigation.h"

IrrigationState irrigationState = IRRIG_OFF;
IrrigationState lastIrrigationState = IRRIG_UNDEFINED;

virtualTimer timer_WTANK_timeout;

unsigned char temperature = 0;
__bit flag_airConditioner = 0;

void run_IrrigationLogic()
{

}
