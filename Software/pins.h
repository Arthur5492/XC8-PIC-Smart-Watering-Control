#ifndef PINS_H
#define PINS_H

///INPUTS

#define pin_soilMoisture   PORTAbits.RA0
#define pin_temperature    PORTAbits.RA1
#define pin_light          PORTAbits.RA2
#define pin_leftButton     PORTBbits.RB1
#define pin_rightButton    PORTBbits.RB2

#define pin_waterLevel_TOP PORTCbits.RC6
#define pin_waterLevel_BOT PORTCbits.RC7
//END INPUTS

///OUTPUTS
//PORTC
#define pin_solenoid        PORTCbits.RC0
#define pin_waterPump       PORTCbits.RC1
#define pin_alarm           PORTCbits.RC2
#define pin_artificialLight PORTCbits.RC3
#define pin_airConditioner  PORTCbits.RC4
//END OUTPUTS

//LCD PINS
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
//END LCD

#endif