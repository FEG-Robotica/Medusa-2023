#include "estrategias.h"
#include "../medusa_motor/Motor.h"
#include "BLEDevice.h"

int leituraLinhaEsq;
int leituraLinhaCentEsq;
int leituraLinhaCentDir;
int leituraLinhaDir;

int leituraLatDir;
int leituraFrontDir;
int leituraLatEsq;
int leituraFrontEsq;
int leituraCentEsq;
int leituraCentDir;
int leituraLatEsq2;
int leituraFrontEsq2;

double velMotor = 75;
int piscou = 0;
int parametroLinha= 2700;

void leituraSensorLinha()
{
  if (analogRead(SENSOR_LINHA_DIR) < parametroLinha)
  {
    leituraLinhaDir = 1;
  }
  else
  {
    leituraLinhaDir = 0;
  }

  if (analogRead(SENSOR_LINHA_ESQ) < parametroLinha)
  {
    leituraLinhaEsq = 1;
  }
  else
  {
    leituraLinhaEsq = 0;
  }

  if (analogRead(SENSOR_LINHA_CENT_ESQ) < parametroLinha)
  {
    leituraLinhaCentEsq = 1;
  }
  else
  {
    leituraLinhaCentEsq = 0;
  }

  if (analogRead(SENSOR_LINHA_CENT_DIR) < parametroLinha)
  {
    leituraLinhaCentDir = 1;
  }
  else
  {
    leituraLinhaCentDir = 0;
  }
}

void leituraSensorDistancia()
{
  if (gpio_get_level(SENSOR_LAT_ESQ) == 1)
  {
    leituraLatEsq = 0;
  }
  else
  {
    leituraLatEsq = 1;
  }

  if (gpio_get_level(SENSOR_FRONT_ESQ) == 1)
  {
    leituraFrontEsq = 0;
  }
  else
  {
    leituraFrontEsq = 1;
  }

  if (gpio_get_level(SENSOR_FRONT_DIR) == 1)
  {
    leituraFrontDir = 0;
  }
  else
  {
    leituraFrontDir = 1;
  }

  if (gpio_get_level(SENSOR_LAT_DIR) == 1)
  {
    leituraLatDir = 0;
  }
  else
  {
    leituraLatDir = 1;
  }

  if (gpio_get_level(SENSOR_CENT_ESQ) == 1)
  {
    leituraCentEsq = 0;
  }
  else
  {
    leituraCentEsq = 1;
  }

//Aqui faltam 2 sensores ! Obs: verificar uso
}

void leituraSensorCorrente(){
  //
}

void busca()
{
  Serial.println("Entrou busca");
  leituraSensorLinha();
  testaLinha();
  leituraSensorDistancia();
  if ((leituraLatEsq == 0) && (leituraFrontEsq == 0) && (leituraFrontDir == 0) && (leituraLatDir == 1))
  {
    moverMotor(D, T, velMotor * 0.6);
    moverMotor(E, F, velMotor * 0.8);
    delay(300);
  }
  else if ((leituraLatEsq == 0) && (leituraFrontEsq == 0) && (leituraFrontDir == 1) && (leituraLatDir == 1))
  {
    moverMotor(D, T, velMotor * 0.6);
    moverMotor(E, F, velMotor * 0.7);
    delay(200);
  }
  else if ((leituraLatEsq == 0) && (leituraFrontEsq == 0) && (leituraFrontDir == 1) && (leituraLatDir == 0))
  {
    moverMotor(D, F, velMotor * 0.6);
    moverMotor(E, F, velMotor * 0.7);
    delay(100);
  }
  else if ((leituraLatEsq == 0) && (leituraFrontEsq == 1) && (leituraFrontDir == 1) && (leituraLatDir == 0))
  {
    moverMotor(D, F, velMotor * 0.95);
    moverMotor(E, F, velMotor * 0.95);
  }
  else if ((leituraLatEsq == 0) && (leituraFrontEsq == 1) && (leituraFrontDir == 0) && (leituraLatDir == 0))
  {
    moverMotor(D, F, velMotor * 0.7);
    moverMotor(E, F, velMotor * 0.6);
    delay(100);
  }
  else if ((leituraLatEsq == 1) && (leituraFrontEsq == 1) && (leituraFrontDir == 0) && (leituraLatDir == 0))
  {
    moverMotor(D, F, velMotor * 0.7);
    moverMotor(E, T, velMotor * 0.6);
    delay(200);
  }
  else if ((leituraLatEsq == 1) && (leituraFrontEsq == 0) && (leituraFrontDir == 0) && (leituraLatDir == 0))
  {
    moverMotor(D, F, velMotor * 0.8);
    moverMotor(E, T, velMotor * 0.6);
    delay(300);
  }
  else if ((leituraLatEsq == 0) && (leituraFrontEsq == 0) && (leituraFrontDir == 0) && (leituraLatDir == 0))
  {
    moverMotor(D, F, velMotor * 0.5);
    moverMotor(E, F, velMotor * 0.6);
    delay(300);
    moverMotor(D, F, velMotor * 0.6);
    moverMotor(E, T, velMotor * 0.7);
    delay(200);
  }
}

void testaLinha()
{
  // 0 branco 1 preto
  // aumentar delay da linha branca
  while (gpio_get_level(START) == 0)
  {
    pararMotor();
  }

  if ((leituraLinhaEsq == 0) && (leituraLinhaDir == 1))
  {
    moverMotor(E, T, velMotor * 0.7);
    moverMotor(D, T, velMotor * 0.7);
    delay(1000);
    moverMotor(E, F, velMotor * 0.5);
    moverMotor(D, T, velMotor * 0.5);
    delay(1000);
  }
  else if ((leituraLinhaEsq == 1) && (leituraLinhaDir == 0))
  {
    moverMotor(D, T, velMotor * 0.7);
    moverMotor(E, T, velMotor * 0.7);
    delay(1000);
    moverMotor(D, F, velMotor * 0.5);
    moverMotor(E, T, velMotor * 0.5);
    delay(1000);
  }
  else if ((leituraLinhaEsq == 1) && (leituraLinhaDir == 1))
  {
    moverMotor(E, F, velMotor * 0.5);
    moverMotor(D, F, velMotor * 0.5);
  }
  else if ((leituraLinhaEsq == 0) && (leituraLinhaDir == 0))
  {
    moverMotor(E, T, velMotor * 0.8);
    moverMotor(D, T, velMotor * 0.8);
    delay(1000);
    moverMotor(E, T, velMotor * 0.7);
    moverMotor(D, F, velMotor * 0.8);
    delay(1000);
  }
}

void testaDistancia()
{
  //
}

void testeDistanciaMotor()
{
  if (leituraLatEsq && !leituraFrontEsq && !leituraCentEsq && !leituraFrontDir && !leituraLatDir)
  { // apenas sensor esquerdo
    moverMotor(T, E, 60);
    moverMotor(F, D, 60);
  }
  else if (!leituraLatEsq && !leituraFrontEsq && leituraCentEsq && !leituraFrontDir && !leituraLatDir)
  { // apenas sensor do centro
    moverMotor(F, E, 100); // MUDAR PRA 100 DEPOIS
    moverMotor(F, D, 100);
  }
  else if (!leituraLatEsq && leituraFrontEsq && !leituraCentEsq && leituraFrontDir && !leituraLatDir)
  { // os frontais das pontas
    moverMotor(F, E, 100); // MUDAR PARA 100
    moverMotor(F, D, 100);
  }
  else if (!leituraLatEsq && leituraFrontEsq && leituraCentEsq && leituraFrontDir && !leituraLatDir)
  { // sensor frontais e central
    moverMotor(F, E, 100); // MUDAR PARA 100
    moverMotor(F, D, 100);
  }
  else if (!leituraLatEsq && !leituraFrontEsq && !leituraCentEsq && leituraFrontDir && !leituraLatDir)
  { // apenas frontal direito
    moverMotor(F, E, 60);
    moverMotor(T, D, 60);
  }
  else if (!leituraLatEsq && !leituraFrontEsq && leituraCentEsq && leituraFrontDir && !leituraLatDir)
  { // frontal direito e central
    moverMotor(F, E, 60);
    moverMotor(T, D, 60);
  }
  else if (!leituraLatEsq && leituraFrontEsq && !leituraCentEsq && !leituraFrontDir && !leituraLatDir)
  { // apenas frontal esquerdo
    moverMotor(T, E, 60);
    moverMotor(F, D, 60);
  }
  else if (!leituraLatEsq && leituraFrontEsq && leituraCentEsq && !leituraFrontDir && !leituraLatDir)
  { // frontal esquerdo e central
    moverMotor(T, E, 60);
    moverMotor(F, D, 60);
  }
  else if (!leituraLatEsq && !leituraFrontEsq && !leituraCentEsq && !leituraFrontDir && leituraLatDir)
  { // apenas direito
    moverMotor(F, E, 60);
    moverMotor(T, D, 60);
  }
  else
  {
    pararMotor();
  }
  if (gpio_get_level(START) == 0)
  {
    pararMotor();
  }
}

void arco()
{
  obterMilis();
  Serial.println(timerMilis);
  if (timerMilis < 500)
  {
    testeDistanciaMotor();
    if (gpio_get_level(START) == 0)
    {
      pararMotor();
    }
  }
  else
  {
    if (!leituraLatDir && !leituraFrontEsq && !leituraCentEsq && !leituraFrontDir && !leituraLatDir)
    {
      moverMotor(D, F, 75); // mudar para 75 porque deu top
      moverMotor(E, F, 90);
      leituraSensorLinha();
      if ((leituraLinhaDir == 1) && (leituraLinhaEsq == 1))
      {

        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        delay(100);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
      }
      else if (leituraLinhaDir == 1)
      {

        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        delay(100);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
      }
      else if (leituraLinhaEsq == 1)
      {

        moverMotor(D, T, 90); // mudar para 75 porque deu top
        moverMotor(E, T, 50);
        delay(100);
        moverMotor(D, T, 90); // mudar para 75 porque deu top
        moverMotor(E, T, 50);
      }
    }
    else if (leituraLatDir && !leituraFrontEsq && !leituraCentEsq && !leituraFrontDir && !leituraLatDir)
    { // apenas sensor esquerdo
      moverMotor(E, T, 60);
      moverMotor(D, F, 60);
    }
    else if (!leituraLatDir && !leituraFrontEsq && leituraCentEsq && !leituraFrontDir && !leituraLatDir)
    { // apenas sensor do centro
      moverMotor(E, F, 100); // MUDAR PRA 100 DEPOIS
      moverMotor(D, F, 100);
    }
    else if (!leituraLatDir && leituraFrontEsq && !leituraCentEsq && leituraFrontDir && !leituraLatDir)
    { // os frontais das pontas
      moverMotor(E, F, 100); // lembrar de mudar para 100 (0 apenas teste)
      moverMotor(D, F, 100);
    }
    else if (!leituraLatDir && leituraFrontEsq && leituraCentEsq && leituraFrontDir && !leituraLatDir)
    { // sensor frontais e central
      moverMotor(E, F, 100); // MUDAR PARA 100
      moverMotor(D, F, 100);
    }
    else if (!leituraLatDir && !leituraFrontEsq && !leituraCentEsq && leituraFrontDir && !leituraLatDir)
    { // apenas frontal direito
      moverMotor(E, F, 60);
      moverMotor(D, T, 60);
    }
    else if (!leituraLatDir && !leituraFrontEsq && leituraCentEsq && leituraFrontDir && !leituraLatDir)
    { // frontal direito e central
      moverMotor(E, F, 60);
      moverMotor(D, T, 60);
    }

    else if (!leituraLatDir && leituraFrontEsq && !leituraCentEsq && !leituraFrontDir && !leituraLatDir)
    { // apenas frontal esquerdo
      moverMotor(E, T, 60);
      moverMotor(D, F, 60);
    }
    else if (!leituraLatDir && leituraFrontEsq && leituraCentEsq && !leituraFrontDir && !leituraLatDir)
    { // frontal esquerdo e central
      moverMotor(E, T, 60);
      moverMotor(D, F, 60);
    }
    else if (!leituraLatDir && !leituraFrontEsq && !leituraCentEsq && !leituraFrontDir && leituraLatDir)
    { // apenas direito
      moverMotor(E, F, 60);
      moverMotor(D, F, 60);
    }
    else
    {
      moverMotor(D, F, 75); // mudar para 75 porque deu top
      moverMotor(E, F, 90);
      leituraSensorLinha();
      if ((leituraLinhaDir == 1) && (leituraLinhaEsq == 1))
      {
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        leituraSensorLinha();
        delay(50);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        delay(50);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
      }
      else if (leituraLinhaDir == 1)
      {
        moverMotor(D, T, 75); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        leituraSensorLinha();
        delay(50);
        moverMotor(D, T, 75); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        delay(50);
        moverMotor(D, T, 75); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
      }
      else if (leituraLinhaEsq == 1)
      {
        moverMotor(D, T, 90); // mudar para 75 porque deu top
        moverMotor(E, T, 50);
        leituraSensorLinha();
        delay(50);
        moverMotor(D, T, 90); // mudar para 75 porque deu top
        moverMotor(E, T, 50);
        delay(50);
        moverMotor(D, T, 90); // mudar para 75 porque deu top
        moverMotor(E, T, 50);
      }
    }
    if (gpio_get_level(START) == 0)
    {
      pararMotor();
    }
    obterMilis();
    if (timerMilis > 2500)
    {
      //Serial.println(timerMilis);
      resetaTimer();
    }
  }
}

void toquinho()
{

  if (timerMilis < 500)
  {
    testeDistanciaMotor();
    if (gpio_get_level(START) == 0)
    {
      pararMotor();
    }
  }
  else
  {
    if (!leituraLatEsq && !leituraFrontEsq && !leituraCentEsq && !leituraFrontDir && !leituraLatDir)
    {
      moverMotor(D, F, 75); // mudar para 75 porque deu top
      moverMotor(E, F, 75);
      leituraSensorLinha();
      if ((leituraLinhaDir == 1) && (leituraLinhaEsq == 1))
      {
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        leituraSensorLinha();
        delay(50);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        delay(50);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
      }
      else if (leituraLinhaDir == 1)
      {
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        leituraSensorLinha();
        delay(50);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        delay(50);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
      }
      else if (leituraLinhaEsq == 1)
      {
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        leituraSensorLinha();
        delay(50);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        delay(50);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
      }
    }
    else if (leituraLatEsq && !leituraFrontEsq && !leituraCentEsq && !leituraFrontDir && !leituraLatDir)
    { // apenas sensor esquerdo
      moverMotor(E, T, 60);
      moverMotor(D, F, 60);
    }
    else if (!leituraLatEsq && !leituraFrontEsq && leituraCentEsq && !leituraFrontDir && !leituraLatDir)
    {                        // apenas sensor do centro
      moverMotor(E, F, 100); // MUDAR PRA 100 DEPOIS
      moverMotor(D, F, 100);
      leituraSensorLinha();
    }
    else if (!leituraLatEsq && leituraFrontEsq && !leituraCentEsq && leituraFrontDir && !leituraLatDir)
    {                        // os frontais das pontas
      moverMotor(E, F, 100); // lembrar de mudar para 100 (0 apenas teste)
      moverMotor(D, F, 100);
      leituraSensorLinha();
    }
    else if (!leituraLatEsq && leituraFrontEsq && leituraCentEsq && leituraFrontDir && !leituraLatDir)
    {                        // sensor frontais e central
      moverMotor(E, F, 100); // MUDAR PARA 100
      moverMotor(D, F, 100);
    }
    else if (!leituraLatEsq && !leituraFrontEsq && !leituraCentEsq && leituraFrontDir && !leituraLatDir)
    { // apenas frontal direito
      moverMotor(E, F, 60);
      moverMotor(D, T, 60);
    }
    else if (!leituraLatEsq && !leituraFrontEsq && leituraCentEsq && leituraFrontDir && !leituraLatDir)
    { // frontal direito e central
      moverMotor(E, F, 60);
      moverMotor(D, T, 60);
    }
    else if (!leituraLatEsq && leituraFrontEsq && !leituraCentEsq && !leituraFrontDir && !leituraLatDir)
    { // apenas frontal esquerdo
      moverMotor(E, T, 60);
      moverMotor(D, F, 60);
    }
    else if (!leituraLatEsq && leituraFrontEsq && leituraCentEsq && !leituraFrontDir && !leituraLatDir)
    { // frontal esquerdo e central
      moverMotor(E, T, 60);
      moverMotor(D, F, 60);
    }
    else if (!leituraLatEsq && !leituraFrontEsq && !leituraCentEsq && !leituraFrontDir && leituraLatDir)
    { // apenas direito
      moverMotor(E, F, 60);
      moverMotor(D, T, 60);
    }
    else
    {
      moverMotor(D, F, 70); // mudar para 75 porque deu top
      moverMotor(E, F, 70);
      leituraSensorLinha();
      if ((leituraLinhaDir == 1) && (leituraLinhaEsq == 1))
      {
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        leituraSensorLinha();
        delay(50);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        delay(50);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
      }
      else if (leituraLinhaDir == 1)
      {
        moverMotor(D, T, 75); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        leituraSensorLinha();
        delay(50);
        moverMotor(D, T, 75); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        delay(50);
        moverMotor(D, T, 75); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
      }
      else if (leituraLinhaEsq == 1)
      {
        moverMotor(D, T, 90); // mudar para 75 porque deu top
        moverMotor(E, T, 50);
        leituraSensorLinha();
        delay(50);
        moverMotor(D, T, 90); // mudar para 75 porque deu top
        moverMotor(E, T, 50);
        delay(50);
        moverMotor(D, T, 90); // mudar para 75 porque deu top
        moverMotor(E, T, 50);
      }
    }
    if (gpio_get_level(START) == 0)
    {
      pararMotor();
    }
    if (timerMilis > 2000)
    {
      resetaTimer();
    }
  }
}

void missil(){
  moverMotor(D,F,100);
  moverMotor(E,F,100);
}

void missilLinha(){
  moverMotor(D,F, 100);
  moverMotor(D,T,100);
  leituraSensorLinha();
      if ((leituraLinhaDir == 1) && (leituraLinhaEsq == 1))
      {

        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        delay(100);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
      }
      else if (leituraLinhaDir == 1)
      {

        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
        delay(100);
        moverMotor(D, T, 50); // mudar para 75 porque deu top
        moverMotor(E, T, 90);
      }
      else if (leituraLinhaEsq == 1)
      {

        moverMotor(D, T, 90); // mudar para 75 porque deu top
        moverMotor(E, T, 50);
        delay(100);
        moverMotor(D, T, 90); // mudar para 75 porque deu top
        moverMotor(E, T, 50);
      }
}

void estrela(){
  if ((leituraLinhaDir == 1) && (leituraLinhaEsq == 1))
  {
    while ((leituraLinhaDir == 1) && (leituraLinhaEsq == 1))
    {
      testeDistanciaMotor();
      moverMotor(D, F, 70);
      moverMotor(D, F, 70);
    }
  }
  else
  {
    if ((leituraLinhaDir == 0) && (leituraLinhaEsq == 1))
    {

      moverMotor(D, F, 60);
      moverMotor(E, T, 60);
      delay(50);
      moverMotor(D, F, 60);
      moverMotor(E, T, 60);
    }

    if ((leituraLinhaDir == 1) && (leituraLinhaEsq == 0))
    {

      moverMotor(D, T, 60);
      moverMotor(E, F, 60);
      delay(50);
      moverMotor(D, T, 60);
      moverMotor(E, F, 60);
    }

    if ((leituraLinhaDir == 0) && (leituraLinhaEsq == 0))
    {
      while ((leituraLinhaDir == 0) || (leituraLinhaEsq == 0))
      {
        moverMotor(D, T, 60);
        moverMotor(E, T, 60);
        delay(50);
        pararMotor();
        delay(50);
        moverMotor(D, T, 60);
        moverMotor(E, F, 60);
      }
    }
    else
    {
      testeDistanciaMotor();
    }
  }
  if (gpio_get_level(START) == 0)
  {
    pararMotor();
  }
}

 