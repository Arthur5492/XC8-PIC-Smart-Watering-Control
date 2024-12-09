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
unsigned char lcd_index = 1;


//Para debounce dos botoes
__bit leftButtonPressed = 0;
__bit rightButtonPressed = 0;
unsigned char lastLeftButtonState = 1;  // Estado anterior do bot�o esquerdo 
unsigned char lastRightButtonState = 1; // Estado anterior do bot�o direito 

extern virtualTimer timer_lcdButtons;

void print_TankState(void);
void print_Index(void);
void lcd_run(void);
void lcd_turnRight(void);
void lcd_turnLeft(void);
void interrupt_checkButton(void);


//Printa Tank State no LCD
void print_TankState(void)
{
  
  if(tankState == lastTankState)
    return;
  
  lastTankState = tankState;
  
  Lcd_Clear();
  char buffer[20];
  
  Lcd_Set_Cursor(1,1);
  Lcd_Write_String("Tank State:");
  
  sprintf(buffer, "%s" ,TankStateString[tankState]);
  
  Lcd_Set_Cursor(2,1);
  Lcd_Write_String(buffer);
}

//so um teste
void print_Index(void)
{
  Lcd_Clear();
  char buffer[20];
  
  Lcd_Set_Cursor(1,1);
  sprintf(buffer, "%d", lcd_index);
  
  Lcd_Write_String(buffer);
}

void lcd_debounceButtons()
{
  // Aguarda o tempo do debounce antes de verificar os botoes
    if (timer_lcdButtons.reached == 0) {
        return; // Sai se o timer ainda nao alcancou o tempo alvo
    }

    // Reseta o timer para debounce
    timer_lcdButtons.reached = 0;

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

virtualTimer timer_lcdButtons = 
{
  .targetTime  = 10,
  .elapsedTime = 0,
  .active = 1,
  .reached = 0
};

#endif