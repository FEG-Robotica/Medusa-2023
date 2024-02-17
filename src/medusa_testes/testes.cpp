#include <Arduino.h>
#include "../main.h"
#include "../medusa_sensores/medusaSENS.h"
#include "../medusa_motor/Motor.h"
#include "../medusa_estrategias/estrategias.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

int antiBreak = 0;
std::string temp;

void testePWMS(){
  pwmASetDuty(100);
  pwmBSetDuty(70);
  pwmCSetDuty(50);
  pwmDSetDuty(30);
}

void frenteLinha(){
      moverMotor(D, F, velMotor); // mudar para 75 porque deu top
      moverMotor(E,F, velMotor);
      leituraSensorLinha();
      if ((leituraLinhaDir == 1) && (leituraLinhaEsq == 1))
      {

        moverMotor(D,T, 50); // mudar para 75 porque deu top
        moverMotor(E,T, 90);
        leituraSensorLinha();
        delay(50);
        moverMotor(D,T, 50); // mudar para 75 porque deu top
        moverMotor(E,T, 90);
        delay(50);
        moverMotor(D,T, 50); // mudar para 75 porque deu top
        moverMotor(E,T, 90);
      }
      else if (leituraLinhaDir == 1)
      {

        moverMotor(D,T, 50); // mudar para 75 porque deu top
        moverMotor(E,T, 90);
        leituraSensorLinha();
        delay(50);
        moverMotor(D,T, 50); // mudar para 75 porque deu top
        moverMotor(E,T, 90);
        delay(50);
        moverMotor(D,T, 50); // mudar para 75 porque deu top
        moverMotor(E,T, 90);
      }
      else if (leituraLinhaEsq == 1)
      {
        moverMotor(D,T, 50); // mudar para 75 porque deu top
        moverMotor(E,T, 90);
        leituraSensorLinha();
        delay(50);
        moverMotor(D,T, 50); // mudar para 75 porque deu top
        moverMotor(E,T, 90);
        delay(50);
        moverMotor(D,T, 50); // mudar para 75 porque deu top
        moverMotor(E,T, 90);
      }

}

void piscaLed(){
    //digitalWrite(LED_ONBOARD, HIGH);
    delay(1000);
    //digitalWrite(LED_ONBOARD, LOW);
    delay(1000);
}

void andarFrente()
{
  moverMotor(E, T, 0);
  moverMotor(D, T, 0);
  moverMotor(E, F, velMotor);
  moverMotor(D, F, velMotor);

}

void andarTras()
{
  moverMotor(E, F, 0);
  moverMotor(D, F, 0);
  moverMotor(E, T, velMotor);
  moverMotor(D, T, velMotor);

}

void testeBLE(){
  std::string texto ;
   if(!leituraLatEsq && leituraFrontEsq && leituraCentEsq && leituraFrontDir  && leituraLatDir){ //apenas sensor esquerdo
                    moverMotor(T,E,60);
                    moverMotor(F,D,60);
                    texto = "SDE";
                    enviaComando(texto);
                }
}

void testeVelPWM(int velocidade){
  temp = std::to_string(velocidade);
  int velA = std::stoi(temp.substr(0, 2).c_str());
  Serial.print("temp");
  Serial.println(temp.c_str());
  delay(1000);
  int velB = std::stoi(temp.substr(2, 2).c_str());

  Serial.println(velB);
  int velC = std::stoi(temp.substr(4, 2).c_str());
  Serial.print(velC);
  int velD = std::stoi(temp.substr(6, 2).c_str());
  Serial.print(velD);

  pwmASetDuty(velA);
  pwmBSetDuty(velB);
  pwmCSetDuty(velC);
  pwmDSetDuty(velD);
}