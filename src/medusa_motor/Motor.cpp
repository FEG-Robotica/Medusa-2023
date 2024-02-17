#include "Motor.h"
#include "../medusa_sensores/medusaSENS.h"

void moverMotor(const bool lado, const bool direcao, int ciclo)
{
    if (lado == E)
    {
        if (direcao == F)
        { // ir para frente
            pwmBSetDuty(0);
            pwmASetDuty(ciclo * corrEsq);
        }

        if (direcao == T)
        { // ir para trás
            pwmASetDuty(0);
            pwmBSetDuty(ciclo * corrEsq);
        }
    }

    if (lado == D)
    {
        if (direcao == F)
        { // ir para frente
            pwmDSetDuty(0);
            pwmCSetDuty(ciclo * corrDir);
        }

        if (direcao == T)
        { // ir para trás
            pwmCSetDuty(0);
            pwmDSetDuty(ciclo * corrDir);
        }
    }
}

void pararMotor()
{
    pwmASetDuty(0);
    pwmBSetDuty(0);
    pwmCSetDuty(0);
    pwmDSetDuty(0);
}