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
volatile unsigned int timerCounter;

typedef struct {
    unsigned int targetTime;
    unsigned int startTime;
    char active;
    void (*callback)(void);
} virtualTimer;


void stopTimer (virtualTimer *timer);
void startTimer(virtualTimer *timer);


void interrupt_updateTimer(virtualTimer *timer);


void runTimer(virtualTimer *timer);
# 1 "virtualTimer.c" 2


volatile unsigned int timerCounter = 0;

void runTimer(virtualTimer *timer)
{
  if(timer->active == 0)
    return;

  unsigned int elapsedTime = timerCounter - timer->startTime;



  if(elapsedTime >= timer->targetTime)
  {
    timer->startTime = timerCounter;

    if(timer->callback != 0)
      timer->callback();
  }

  return;
}

void startTimer(virtualTimer *timer)
{
  if(timer->active)
    return;

  timer->startTime = timerCounter;
  timer->active = 1;
}


void stopTimer(virtualTimer *timer)
{
  if(timer->active == 0)
    return;

  timer->active = 0;
}
