# 1 "irrigation.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "irrigation.c" 2
# 1 "./irrigation.h" 1








# 1 "./pins.h" 1
# 9 "./irrigation.h" 2

# 1 "./virtualTimer.h" 1
# 11 "./virtualTimer.h"
extern unsigned int timerCounter;




typedef struct {
    unsigned int targetTime;
    unsigned int elapsedTime;
    char active;

    char reached;
} virtualTimer;



void stopTimer (virtualTimer *timer);
void startTimer(virtualTimer *timer);


void interrupt_updateTimer(virtualTimer *timer);


void runTimer(virtualTimer *timer);
# 10 "./irrigation.h" 2


typedef enum
{
  IRRIG_UNDEFINED = -1,
  IRRIG_ON,
  IRRIG_OFF,
  IRRIG_ERROR
}IrrigationState;

extern IrrigationState irrigationState;
extern IrrigationState lastIrrigationState;

extern virtualTimer timer_WTANK_timeout;

extern unsigned char temperature;
extern unsigned char maxTemperature;
extern __bit flag_airConditioner;
# 1 "irrigation.c" 2


IrrigationState irrigationState = IRRIG_OFF;
IrrigationState lastIrrigationState = IRRIG_UNDEFINED;

virtualTimer timer_WTANK_timeout;

unsigned char temperature = 0;
__bit flag_airConditioner = 0;

void run_IrrigationLogic()
{

}
