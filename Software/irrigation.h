/**
 * @file irrigation.h
 * @brief Controls the irrigation system, managing water pump activation and integrating data from various sensors.
 * @details Implements thresholds for soil moisture, temperature, and humidity to ensure efficient irrigation.
 *          Handles critical errors and provides overrides for testing and forced operation.
 * @note Logic prioritizes soil moisture, with additional safeguards for temperature limits.
 */

#include "pins.h"
#include "virtualTimer.h"

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



