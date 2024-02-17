#include <Arduino.h>
#include "../main.h"
#include "../medusa_sensores/medusaSENS.h"
#include "../medusa_motor/Motor.h"
#include "../medusa_estrategias/estrategias.h"

#ifndef TESTES_H
#define TESTES_H

void testeVelPWM(int velocidade);
void testePWMS();
void piscaLed();
void andarFrente();
void andarTras();
void testeBLE();
void frenteLinha();

#endif
