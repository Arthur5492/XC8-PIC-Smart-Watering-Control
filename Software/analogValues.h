/**
 * @file analogValues.h
 */

#include <xc.h>

typedef enum 
{
  CH_SOILMOISTURE = 0,
  CH_TEMPERATURE  = 1,
  CH_LIGHT = 2
} AnalogicChannels;

extern int soilMoisture;
extern int temperature;
extern int light;

void readTemperature(void);

void readSoilMoisture(void);

void readLight(void);
  

