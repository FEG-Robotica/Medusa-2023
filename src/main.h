#include <Arduino.h>
//#include "../hachiko_sensores/hachikoSENS.h"

#ifndef MAIN_H
#define MAIN_H

extern unsigned long long timerMilis;

void resetaTimer();

void obterMilis();

unsigned long long obterTimer();

void enviaComando(std::string textoComando);

#endif