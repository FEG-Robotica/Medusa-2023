/*
 * File:   sonicPWM.cpp
 * Author: Hiro
 *
 * Created on 03 de Dezembro de 2021, 23:39
 */

#include "medusaPWM.h"

void configPWM(){

    mcpwm_config_t pwm_config;

    pwm_config.frequency = 33000;                          /*!<frequência = 500Hz,*/
    pwm_config.cmpr_a = 0;                                /*Ciclo de trabalho (duty cycle) do PWMxA = 0*/
    pwm_config.cmpr_b = 0;                                /*Ciclo de trabalho (duty cycle) do PWMxb = 0*/                             /*Ciclo de trabalho (duty cycle) do PWMxd = 0*/
    pwm_config.counter_mode = MCPWM_UP_COUNTER;           /*Para MCPWM assimetrico*/
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;             /*Define ciclo de trabalho em nível alto*/

    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, PWMA);         /*!< Utiliza unidade 0 de geração para PWMA*/
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, PWMB);         /*!< Utiliza unidade 0 de geração para PWMB*/
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, PWMC);         /*!< Utiliza unidade 0 de geração para PWMC*/
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, PWMD);         /*!< Utiliza unidade 0 de geração para PWMD*/
}

void pwmASetDuty(float duty) {
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, duty);  /*!< define duty cicle PWMA*/
}

void pwmBSetDuty(float duty) {
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, duty); /*!< define duty cicle PWMN*/
}

void pwmCSetDuty(float duty) {
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, duty); /*!< define duty cicle PWMN*/
}

void pwmDSetDuty(float duty) {
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, duty); /*!< define duty cicle PWMN*/
}
