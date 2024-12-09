/**
 * @file pins.h
 * @brief Definicoes de mapeamento de pinos do microcontrolador.
 * @details Contem macros para facilitar o acesso e a manipulacao dos pinos de entrada, saida e do display LCD.
 */

#ifndef LCDFUNCTIONS_H
#define LCDFUNCTIONS_H

#include "lcd.h"
#include "pins.h"

#include "waterTankManager.h" //Recebe variavel: TankState tankState;

//Array com os enums em formato de string para printar no LCD
const char* TankStateString[] = 
{
  [WTANK_LOW]     = "VAZIO",
  [WTANK_MID]     = "MEIO",
  [WTANK_FULL]    = "CHEIO",
  [WTANK_ERROR]   = "ERRO",
};

//Para rotar entre as paginas do LCD
unsigned char lcd_index      = 1;
unsigned char lcd_lastIndex  = 1;

//Para debounce dos botoes
unsigned char lastLeftButtonState = 1;  // Estado anterior do botão esquerdo (assumindo HIGH como padrão)
unsigned char lastRightButtonState = 1; // Estado anterior do botão direito (assumindo HIGH como padrão)



void print_TankState(void);
void print_Index(void);
void lcd_run(void);
void lcd_turnRight(void);
void lcd_turnLeft(void);
void interrupt_checkButton(void);


//Printa Tank State no LCD
void print_TankState(void)
{
  char buffer[20];
  
  Lcd_Set_Cursor(1,1);
  Lcd_Write_String("Tank State:");
  
  sprintf(buffer, "%s" ,TankStateString[tankState]);
  
  Lcd_Set_Cursor(2,1);
  Lcd_Write_String(buffer);
}

void print_Index(void)
{
  char buffer[20];
  Lcd_Clear();
  
  Lcd_Set_Cursor(1,1);
  sprintf(buffer, "%d", lcd_index);
  
  Lcd_Write_String(buffer);
}

void lcd_run(void)
{
    // Verifica se o indice mudou
  if (lcd_index == lcd_lastIndex)
    return; 
  
  lcd_lastIndex = lcd_index;
  
  switch(lcd_index)
  {
  case 1:
    //print_TankState();
    print_Index();
    break;
  case 2:
    //irrigation();
    print_Index();
    break;
  case 3:
    print_Index();
    break;
  case 4:
    print_Index();
    break;
  default:
    print_Index();
    break;
  };
  return;
}

void lcd_turnRight(void)
{
  //Volta ao index inicial
  if(lcd_index >= 4)
    lcd_index = 1;
  else
    lcd_index++;  
};

void lcd_turnLeft(void)
{
  //Volta ao index final
  if(lcd_index <= 1)
    lcd_index = 4;
  else
    lcd_index--;
};

void interrupt_checkButton(void)
{
  unsigned char leftButtonState = pin_leftButton;  // Leia o estado atual do botão esquerdo
  unsigned char rightButtonState = pin_rightButton; // Leia o estado atual do botão direito

  // Verifica se o estado do botao esquerdo mudou e estabilizou
  if (leftButtonState != lastLeftButtonState && leftButtonState == 0) {
      lcd_turnLeft();  // Ação ao pressionar o botão esquerdo
  }

  // Verifica se o estado do botao direito mudou e estabilizou
  if (rightButtonState != lastRightButtonState && rightButtonState == 0) {
      lcd_turnRight(); // Ação ao pressionar o botão direito
  }

  // Atualiza o estado anterior dos botões
  lastLeftButtonState = leftButtonState;
  lastRightButtonState = rightButtonState;
}

virtualTimer timer_lcdButtons = 
{
  .targetTime  = 50,
  .elapsedTime = 0,
  .active = 0,
  .callback = interrupt_checkButton
};

#endif