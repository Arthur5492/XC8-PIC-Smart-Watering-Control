/**
 * @file waterTankManager.h
 * @brief Gerenciamento do sistema de controle de tanque de agua.
 * @details Declaracoes das funcoes e variaveis necessarias para monitorar o estado do tanque de agua, controlar o enchimento
 *          e gerenciar os sensores de nivel. Inclui integracao com timers virtuais para controle de tempo.
 */

#ifndef WATERTANKMANAGER_H
#define WATERTANKMANAGER_H

#include <xc.h>
#include "pins.h"
#include "virtualTimer.h"

typedef enum
{
  WTANK_UNDEFINED = -1,
  WTANK_FULL,
  WTANK_MID,
  WTANK_LOW,
  WTANK_ERROR
}TankState;

extern TankState tankState;
extern TankState lastTankState;
//timeout para desligar solenoide
extern virtualTimer timer_WTANK_Timeout;

extern __bit isFilling;

//Verifica com base nos sensores de nivel de agua o status do tanque de agua
void check_TankStatus(void);

//Executa a logica de enchimento de tanque baseado no estado atual do tanque
void run_waterTankLogic(void);

//Reseta estado do tanque para valor default
void resetTankState(void);

//Liga solenoide
void startFilling(void);

//Desliga solenoide
void stopFilling(void);

void interrupt_WTANK_timeout(void);

#endif
