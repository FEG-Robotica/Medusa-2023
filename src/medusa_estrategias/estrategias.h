#include <Arduino.h>
#include "../main.h"
#include "../medusa_sensores/medusaSENS.h"
#include "../medusa_motor/Motor.h"

#ifndef ESTRATEGIAS_H
#define ESTRATEGIAS_H

extern int leituraLinhaEsq;
extern int leituraLinhaCentEsq;
extern int leituraLinhaCentDir;
extern int leituraLinhaDir;

extern int leituraLatDir;
extern int leituraFrontDir;
extern int leituraLatEsq;
extern int leituraFrontEsq;
extern int leituraCentEsq;
extern int leituraCentDir;
extern int leituraLatEsq2;
extern int leituraFrontEsq2;

extern double velMotor;

extern int piscou;

typedef enum
{
    PARAR_CMD = 0,
    LED_CMD = 1,
    STRAT1_CMD = 2,
    STRAT2_CMD = 3,
    STRAT3_CMD = 4,
    STRAT4_CMD = 5,
    LEIT_LINHA_CMD = 6,
    LEIT_DIST_CMD = 7,
    FRENTE_CMD = 8,
    LINHA_CMD = 9,
    TRAS_CMD = 10,
    TESTEPWM_CMD = 11,
    ESTRELA_CMD = 12,
    TOQUINHO_CMD = 13,
    ARCO_CMD = 14,
    TESTEPWMS_CMD = 15,
    DISTMOTOR_CMD = 16,
    FRENTELINHA_CMD = 17,
    MISSIL_CMD = 18,
    MISSIL_LINHA_CMD = 19
} command_t;

void busca();

void leituraSensorLinha();

void leituraSensorDistancia();

void leituraSensorCorrente();

void testaLinha();

void testaDistancia();

void testeDistanciaMotor();

void arco();

void toquinho();

void estrela();

void missil();

void missilLinha();

#endif