/*
 * File:   sonicPWM.h
 * Author: Hiro
 *
 * Created on 03 de Dezembro de 2021, 23:39
 */

#include <Arduino.h>
#include "driver/mcpwm.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MEDUSA_PWM_H
#define MEDUSA_PWM_H

#define PWMA GPIO_NUM_23 //PWMA
#define PWMB GPIO_NUM_1 //PWMB
#define PWMC GPIO_NUM_18 //PWMC
#define PWMD GPIO_NUM_19 //PWMD

/**
 * @brief Configuração PWM
 *          
 *        Configura frequência, modo assimétrico, ciclo de trabalho, deadtime, unidade de geração
 *        e pinos de PWM
 * 
 */
void configPWM();

/**
 * @brief Define ciclo de trabalho do PWMA
 * 
 * @param duty porcentagem do ciclo de trabalho i.e para 50% de ciclo de trabalho, duty = 50.0
 */
void pwmASetDuty(float duty);

/**
 * @brief Define ciclo de trabalho do PWMB
 * 
 * @param duty porcentagem do ciclo de trabalho i.e para 50% de ciclo de trabalho, duty = 50.0
 */
void pwmBSetDuty(float duty);

/**
 * @brief Define ciclo de trabalho do PWMC
 * 
 * @param duty porcentagem do ciclo de trabalho i.e para 50% de ciclo de trabalho, duty = 50.0
 */
void pwmCSetDuty(float duty);

/**
 * @brief Define ciclo de trabalho do PWMD
 * 
 * @param duty porcentagem do ciclo de trabalho i.e para 50% de ciclo de trabalho, duty = 50.0
 */
void pwmDSetDuty(float duty);

#endif

#ifdef __cplusplus
}
#endif