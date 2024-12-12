/**
 * @file pins.h
 * @brief Definicoes de mapeamento de pinos do microcontrolador.
 * @details Contem macros para facilitar o acesso e a manipulacao dos pinos de entrada, saida e do display LCD.
 * @warning Nao consegui criar um lcdFunctions.h pois a lib lcd.h nao tem um .c, causando problemas que deixaram tudo mais dificil
 */

#ifndef LCDFUNCTIONS_H
#define LCDFUNCTIONS_H

#include "lcd.h"
#include "pins.h"

#include "waterTankManager.h" //Recebe variavel: TankState tankState;
#include "irrigation.h"

//Array com os enums em formato de string para printar no LCD
char* TankStateString[] = 
{
  [WTANK_LOW]     = "VAZIO",
  [WTANK_MID]     = "MEIO",
  [WTANK_FULL]    = "CHEIO",
  [WTANK_ERROR]   = "ERRO",
};

char* IrrigationStateString[] = 
{
  [IRRIG_ON]    = "ON",
  [IRRIG_OFF]   = "OFF",
  [IRRIG_ERROR] = "ERROR"
};

//Para rotar entre as paginas do LCD
unsigned char lcd_maxIndex = 5;
unsigned char lcd_index = 1;
unsigned char lcd_lastIndex = 0;


//Para debounce dos botoes
__bit leftButtonPressed = 0;
__bit rightButtonPressed = 0;
unsigned char lastLeftButtonState = 1;  // Estado anterior do botï¿½o esquerdo 
unsigned char lastRightButtonState = 1; // Estado anterior do botï¿½o direito 

extern virtualTimer timer_lcdButtons;

void print_TankState(void);
void print_Irrigation(void);
void print_ArtificialLight(void);
void print_Temperature(void);

void lcd_run(void);
void lcd_turnRight(void);
void lcd_turnLeft(void);
void interrupt_checkButton(void);

void draw_Index()
{ 
  char temp_index[3] = {lcd_index + '0' , '/' , lcd_maxIndex + '0' };
  Lcd_Set_Cursor(2,14);
  Lcd_Write_String(temp_index);
}

//Printa Tank State no LCD
void print_TankState(void)
{
  
  if(tankState == lastTankState && lcd_lastIndex == lcd_index)
    return;
  
  lastTankState = tankState;
  
  Lcd_Clear();
  
  Lcd_Set_Cursor(1,2);
  Lcd_Write_String("ESTADO TANQUE");

  Lcd_Set_Cursor(2,6);
  Lcd_Write_String( TankStateString[tankState] );
  
  draw_Index();
}

void print_Irrigation(void)
{
  
  if(irrigationState == lastIrrigationState && lcd_lastIndex == lcd_index)
    return;
  
  lastIrrigationState = irrigationState;
  
  Lcd_Clear();
  
  Lcd_Set_Cursor(1,2);
  Lcd_Write_String("IRRIGACAO:");
  
  Lcd_Set_Cursor(2,4);
  Lcd_Write_String( IrrigationStateString[irrigationState] );
  
  draw_Index();
}

void print_SoilMoisture()
{
  if(soilMoisture == old_soilMoisture && lcd_lastIndex == lcd_index)
    return;
  
  old_soilMoisture = soilMoisture;
  
  Lcd_Clear();
  
  char buffer[16];
  
  ///HUMIDADE SOLO
  Lcd_Set_Cursor(1,2);
  Lcd_Write_String("UMIDADE SOLO");
  
  Lcd_Set_Cursor(2,6);
  sprintf(buffer,"%d",soilMoisture);
  Lcd_Write_String(buffer);
  Lcd_Write_Char('%');
  
  draw_Index();
}
void print_ArtificialLight(void)
{
  if(light == old_light &&  lcd_lastIndex == lcd_index )
    return;
  
  old_light = light;
  
  Lcd_Clear();
  
  Lcd_Set_Cursor(1,2);
  Lcd_Write_String("LUZ ARTIFICIAL");
  
  Lcd_Set_Cursor(2,4);
  if(pin_artificialLight == 0)
    Lcd_Write_String("LIGADA");
  else 
    Lcd_Write_String("DESLIGADA");
  
  draw_Index();
}

void print_Temperature()
{
  if(temperature == old_temperature && lcd_lastIndex == lcd_index)
    return;
  
  old_temperature = temperature;
  
  Lcd_Clear();
  
  char buffer[16];
  
  Lcd_Set_Cursor(1,3);
  Lcd_Write_String("TEMPERATURA:");
  
  Lcd_Set_Cursor(2,7);
  
  sprintf(buffer,"%d",temperature);
  Lcd_Write_String(buffer);//0 - 150
  Lcd_Write_Char((char)223);// 223 = ASCII(º)
  Lcd_Write_Char('C');
  
    
  draw_Index();
}

void lcd_debounceButtons()
{
//  __delay_ms(50);
  // Checa se houve transicao de estado no botao esquerdo
  if (pin_leftButton == 0 && lastLeftButtonState != 0) {
      lcd_turnLeft(); // Acao para o botao esquerdo
  }

  // Checa se houve transicao de estado no botao direito
  if (pin_rightButton == 0 && lastRightButtonState != 0) {
      lcd_turnRight(); // Acao para o botao direito
  }

  // Atualiza os estados anteriores dos botoes
  lastLeftButtonState = pin_leftButton;
  lastRightButtonState = pin_rightButton;
}

void lcd_run(void)
{  
  
  lcd_debounceButtons();
  
  switch(lcd_index)
  {
  case 1:
    print_TankState();
    break;
  case 2:
    print_Irrigation();
    break;
  case 3:
    print_SoilMoisture();
    break;
  case 4:
    print_Temperature();
    break;
  case 5:
    print_ArtificialLight();
  default:
    break;
  };
  
  lcd_lastIndex = lcd_index;
}

void lcd_turnRight(void)
{
  //Volta ao index inicial
  if(lcd_index >= lcd_maxIndex)
    lcd_index = 1;
  else
    lcd_index++;  
};

void lcd_turnLeft(void)
{
  //Volta ao index final
  if(lcd_index <= 1)
    lcd_index = lcd_maxIndex;
  else
    lcd_index--;
};

#endif