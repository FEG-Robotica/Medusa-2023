#include <Arduino.h>
#include "medusa_pwm/medusaPWM.h"
#include "medusa_sensores/medusaSENS.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MOTOR_H
#define MOTOR_H

extern double corrDir;
extern double corrEsq;

const bool F = 1;
const bool T = 0;

const bool E = 1;
const bool D = 0;

void moverMotor(const bool lado, const bool direcao, int ciclo);

void pararMotor();

#endif

#ifdef __cplusplus
}
#endif