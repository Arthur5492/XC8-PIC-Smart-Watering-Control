# 1 "virtualTimer.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "virtualTimer.c" 2
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
# 1 "virtualTimer.c" 2


unsigned int timerCounter = 0;

void runTimer(virtualTimer *timer)
{
  if(timer->active == 0)
    return;

  if(timer->elapsedTime >= timer->targetTime)
  {
    timer->reached = 1;

    timer->elapsedTime = 0;
    return;
  }

  timer->elapsedTime++;
}

void startTimer(virtualTimer *timer)
{
  timer->active = 1;
  timer->elapsedTime = 0;
}


void stopTimer(virtualTimer *timer)
{
  timer->active = 0;
  timer->elapsedTime = 0;
}
