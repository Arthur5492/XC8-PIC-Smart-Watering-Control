#include "virtualTimer.h"

volatile unsigned int timerCounter = 0;

void runTimer(virtualTimer *timer)
{
  if(timer->active == 0)
    return;
  
  //Se tempo definido foi alcancado
  if(timerCounter >= timer->targetTime)
  {
//    timer->elapsedTime = 0;
    
    if(timer->callback != 0)
      timer->callback();
    
    return;
  }
  
//  timer->elapsedTime++;
}

void startTimer(virtualTimer *timer)
{
  if(timer->active)
    return;
  
  timer->active = 1;
  timer->elapsedTime = 0;
}
  

void stopTimer(virtualTimer *timer)
{
  if(timer->active == 0)
    return;
  
  timer->active = 0;
  timer->elapsedTime = 0;
}

/*
void configTimer(virtualTimer *timer, unsigned int t_targetTime, unsigned int t_elapsedTime, void (*t_callback)() )
{
  set_targetTime(timer, t_targetTime);
  set_elapsedTime(timer,t_elapsedTime);
  set_callback(timer, t_callback);
}

void set_targetTime(virtualTimer *timer, unsigned int t_targetTime){ 
  timer->targetTime = t_targetTime; 
///}

void set_elapsedTime(virtualTimer *timer, unsigned int t_elapsedTime){
  timer->elapsedTime = t_elapsedTime; 
}

void set_callback(virtualTimer *timer, void (*t_callback)() ){ 
  timer->callback = t_callback; 
}
 */

