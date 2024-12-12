#include "virtualTimer.h"

volatile unsigned int timerCounter = 0;

void runTimer(virtualTimer *timer)
{
  if(timer->active == 0)
    return;
  
  unsigned int elapsedTime = timerCounter - timer->startTime;
  
  
  //Se tempo definido foi alcancado
  if(elapsedTime  >= timer->targetTime)
  {
    timer->startTime = timerCounter; // Reinicia o timer
    
    if(timer->callback != 0)
      timer->callback();
  }
  
  return;
}

void startTimer(virtualTimer *timer)
{
  if(timer->active)
    return;
  
  timer->startTime = timerCounter; // Salva o tempo inicial
  timer->active = 1; // Ativa timer
}
  

void stopTimer(virtualTimer *timer)
{
  if(timer->active == 0)
    return;
  
  timer->active = 0;
}

/*
void configTimer(virtualTimer *timer, unsigned int t_targetTime, unsigned int t_elapsedTime, void (*t_callback)() )
{
  set_targetTime(timer, t_targetTime);
  set_callback(timer, t_callback);
}

void set_targetTime(virtualTimer *timer, unsigned int t_targetTime){ 
  timer->targetTime = t_targetTime; 
///}

void set_callback(virtualTimer *timer, void (*t_callback)() ){ 
  timer->callback = t_callback; 
}
 */

