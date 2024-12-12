/**
 * @file virtualTimer.h
 * @brief Gerenciamento de timers virtuais, eh possival fazer multiplos timers apenas com um timer fisico rodando
 * @details Ha uma variavel contadora timerCounter incrementando na interrupcao do timer1 a cada 0,5s ela eh incrementada
 * Todos os virtualTimers tem a funcao runTimer() que verifica o valor em que o contador na interrupcao esta
 * Se o timerCounter estiver com o mesmo valor que o tempo alvo do virtualTimer, uma funcao callback designada ao timerVirtual eh executada.
 */
#ifndef VIRTUALTIMER_H
#define VIRTUALTIMER_H

volatile unsigned int timerCounter;

typedef struct {
    unsigned int targetTime;    // Intervalo desejado (em ms)
    char active;              // Flag para ativar/desativar timer
    void (*callback)(void);       // Ponteiro para a funcao de callback
} virtualTimer;

//ativa ou desativa timer
void stopTimer (virtualTimer *timer);
void startTimer(virtualTimer *timer);

//funcao para executar na interrupcao
void interrupt_updateTimer(virtualTimer *timer);

//funcao para executar logica na main
void runTimer(virtualTimer *timer);

//void configTimer(virtualTimer *timer, unsigned int t_targetTime, unsigned int t_elapsedTime, void (*t_callback)() );
//
//void set_targetTime(virtualTimer *timer, unsigned int t_targetTime);
//void set_elapsedTime(virtualTimer *timer, unsigned int t_elapsedTime);
//void set_callback(virtualTimer *timer, void (*t_callback)() );

#endif