/**
 * @file virtualTimer.h
 * @brief Gerenciamento de timers virtuais.
 * @details Contem a definicao da estrutura virtualTimer e funcoes para configurar, controlar e executar timers
 *          baseados em contagem de tempo virtual. Os timers virtuais permitem criar temporizadores independentes 
 *          sem depender de multiplos timers fisicos.
 */
#ifndef VIRTUALTIMER_H
#define VIRTUALTIMER_H

extern unsigned int timerCounter;

// Defina o protótipo esperado para o callback
//typedef void (*TimerCallback)(void); // Ponteiro de funcao que nao recebe nem retorna nada

typedef struct {
    unsigned int targetTime;    // Intervalo desejado (em ms)
    unsigned int elapsedTime;     // Tempo decorrido (em ms)
    char active;              // Flag para ativar/desativar timer
//    void (*callback)(void);       // Ponteiro para a funcao de callback  Muito custoso
    char reached;
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