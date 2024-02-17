/*
     S S       S S
     D L       L D
     B A _____ B C
 SDA|             |SDD
    |             |
    |_           _|
    |_|_________|_|
     A           B
*/

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "medusa_estrategias/estrategias.h"
#include "medusa_sensores/medusaSENS.h"
#include "medusa_pwm/medusaPWM.h"
#include "medusa_motor/Motor.h"
#include "medusa_estrategias/estrategias.h"
#include "medusa_testes/testes.h"


#define SERVICE_UUID "9ce9a578-2e0b-44fb-ba17-ce974afafc5d"
#define CHARACTERISTIC_UUID "8b9a326c-a555-48a0-8fab-75faa23e0e7f"
#define COM_UUID "9295411b-0868-4655-9b84-ec3a4c74e258"
#define LINHA_UUID "cba1d466-344c-4be3-ab3f-189f80dd7518"
#define DIST_UUID "ca73b3ba-39f6-4ab3-91ae-186dc9577d99"
#define CORR_UUID "c5eb29d0-26c2-4584-84e1-8961803c1567"
#define bleRobo "medusa"
#define ESP_INTR_FLAG_DEFAULT 0

hw_timer_t * timer = NULL;

unsigned long long timerMilis = 0;

command_t comando = ARCO_CMD;

int velocidade = 01010101;
double corrDir = 1.0;
double corrEsq = 1.0;

bool deviceConnected = false ;
bool oldDeviceConnected = false ;
bool bleBool = false ;
bool houveInterrupt = false;

BLEServer* pServer = NULL;

BLECharacteristic bleComCharacteristics(COM_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bleComDescriptor(BLEUUID((uint16_t)0x2902));

BLECharacteristic bleLinhaCharacteristics(LINHA_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bleLinhaDescriptor(BLEUUID((uint16_t)0x2902));

BLECharacteristic bleDistanciaCharacteristics(DIST_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bleDistanciaDescriptor(BLEUUID((uint16_t)0x2902));

BLECharacteristic bleCorrenteCharacteristics(CORR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bleCorrenteDescriptor(BLEUUID((uint16_t)0x2902));

// Setup callbacks onConnect and onDisconnect
class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
    //Serial.println("CONECTADO");
  };
  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
    pServer->startAdvertising();
    //Serial.println("DESCONECTADO");
  }
};

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue();

    Serial.println(value.c_str());

    if (value == "STRAT1" || value == "strat1")
    {
      comando = STRAT1_CMD;
    }

    if(value == "TOQUINHO" || value == "toquinho"){
      comando = TOQUINHO_CMD ;
    }

    if(value == "ARCO" || value == "arco"){
      comando = ARCO_CMD ;
    }

    if(value == "ESTRELA" || value == "estrela"){
      comando = ESTRELA_CMD ;
    }

    if(value == "DISTMOTOR" || value == "distmotor"){
      comando = DISTMOTOR_CMD ;
    }

    if (value == "FRENTE" || value == "frente")
    {
      comando = FRENTE_CMD;
    }

    if (value == "TRAS" || value == "tras")
    {
      comando = TRAS_CMD;
    }

    if(value == "frentelinha"){
      comando = FRENTELINHA_CMD ;
    }

    if (value == "TESTEPWMS" || value == "testepwms")
    {
      comando = TESTEPWMS_CMD;
    }

    if(value == "missil"){
      comando = MISSIL_LINHA_CMD;
    }

    if(value == "missils"){
      comando = MISSIL_CMD;
    }

    if (value == "LED" || value == "led")
    {
      comando = LED_CMD;
    }

    if (value == "B0" || value == "b0")
    {
      bleBool = false;
    }

    if (value == "B1" || value == "b1")
    {
      bleBool = true;
      Serial.println("B1");
    }

    if (value == "P" || value == "p")
    {
      comando = PARAR_CMD;
    }

    if (value.substr(0, 3) == "PWM")
    {
      comando = TESTEPWM_CMD;
      // Serial.println(value.substr(0,3).c_str());
      velocidade = std::stoi(value.substr(3, 11).c_str());
      // Serial.println(velocidade);
      delay(10);
    }

    if(value.substr(0,3) == "vel"){
      velMotor = std::stoi(value.substr(3,6));
    }

    if (value.substr(0, 3) == "esq")
    {
      corrEsq = std::stoi(value.substr(3, 6));
    }

    if (value.substr(0, 3) == "dir")
    {
      corrDir = std::stoi(value.substr(3, 6));
    }


  }

  void onRead(BLECharacteristic *pCharacteristic)
  {
    //
  }
};

void IRAM_ATTR start_ISR_handler()
{
  pararMotor();
  comando = PARAR_CMD;
  //digitalWrite(LED_ONBOARD, HIGH);
  houveInterrupt = true;
}

/*
void IRAM_ATTR linhaDir_ISR_handler()
{
  moverMotor(D, T, 60);
  moverMotor(E, T, 60);
  delay(100);
  moverMotor(D, F, 60);
  moverMotor(E, T, 50);
  Serial.println("INTERRUPT");
}

void IRAM_ATTR linhaEsq_ISR_handler()
{
  pararMotor();
}
*/

void iniciarTimer(){
  timer = timerBegin(0, 80, true);
  timerAlarmWrite(timer, 0, true);
  timerAlarmEnable(timer);
}

void resetaTimer(){
  timerWrite(timer,0);
  //timerAlarmWrite(timer, 0, true);
  timerMilis = 0;
}

void pararTimer(){
  timerEnd(timer);
  timer = NULL;
}

void obterMilis(){
  timerMilis = timerReadMilis(timer);
  //Serial.println(timerMilis);
}

unsigned long long obterTimer(){
  return timerReadMilis(timer);
}

void enviaDist()
{
  leituraSensorDistancia();
  std::string sensores = "LE:";
  sensores.append(std::to_string(leituraLatEsq));
  sensores.append("FE:");
  sensores.append(std::to_string(leituraFrontEsq));
  sensores.append("C:");
  sensores.append(std::to_string(leituraCentEsq));
  sensores.append("FD:");
  sensores.append(std::to_string(leituraFrontDir));
  sensores.append("LD:");
  sensores.append(std::to_string(leituraLatDir));
  bleDistanciaCharacteristics.setValue(sensores);
  bleDistanciaCharacteristics.notify();
  delay(10);
}

void enviaLinha()
{
  std::string sensores = "LESQ:";
  sensores.append(std::to_string(analogRead(SENSOR_LINHA_ESQ)));
  sensores.append(" LDIR:");
  sensores.append(std::to_string(analogRead(SENSOR_LINHA_DIR)));
  bleLinhaCharacteristics.setValue(sensores);
  bleLinhaCharacteristics.notify();
  delay(10);
}

void enviaCorrente(){
  /*
  std::string sensores = "CESQ:";
  sensores.append(std::to_string(analogRead(SENSOR_CORRENTE_ESQ)));
  sensores.append(" CDIR:");
  sensores.append(std::to_string(analogRead(SENSOR_CORRENTE_DIR)));
  bleCorrenteCharacteristics.setValue(sensores);
  bleCorrenteCharacteristics.notify();
  delay(10);
  */
  std::string sensores = "START";
  sensores.append(std::to_string(gpio_get_level(START)));
  if(houveInterrupt){
    sensores.append(" com interrupt");
  } else {
    sensores.append(" sem interrupt");
  }

  bleCorrenteCharacteristics.setValue(sensores);
  bleCorrenteCharacteristics.notify();
  delay(10);
}

void enviaComando(std::string textoComando){
  bleComCharacteristics.setValue(textoComando);
  bleComCharacteristics.notify();
  delay(10);
}

void setup()
{
  Serial.begin(9600);
  configGpio();
  configLinha();
  configPWM();
  iniciarTimer();

  BLEDevice::init(bleRobo);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
          CHARACTERISTIC_UUID,
          BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY);

  pService->addCharacteristic(&bleComCharacteristics);
  bleComDescriptor.setValue("bleCom");
  bleComCharacteristics.addDescriptor(&bleComDescriptor);

  pService->addCharacteristic(&bleDistanciaCharacteristics);
  bleDistanciaDescriptor.setValue("bleDist");
  bleDistanciaCharacteristics.addDescriptor(&bleDistanciaDescriptor);

  pService->addCharacteristic(&bleLinhaCharacteristics);
  bleLinhaDescriptor.setValue("bleLinha");
  bleLinhaCharacteristics.addDescriptor(&bleLinhaDescriptor);

  pService->addCharacteristic(&bleCorrenteCharacteristics);
  bleCorrenteDescriptor.setValue("bleCorr");
  bleCorrenteCharacteristics.addDescriptor(&bleCorrenteDescriptor);

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello World");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  pAdvertising->start();

  attachInterrupt(START, start_ISR_handler, FALLING);
  //pinMode(LED_ONBOARD, OUTPUT);
}

void loop()
{
  //Serial.println(gpio_get_level(START));`

  while (gpio_get_level(START) == 0)
  {
    pararMotor();
    //bleComCharacteristics.setValue("START ZERO");
    //bleComCharacteristics.notify();
    //delay(10);
    Serial.println("START IGUAL ZERO");
  }

  if (deviceConnected)
  {
    //Serial.println("Conectado");
    enviaDist();
    enviaLinha();
    enviaCorrente();
  }

  if (!deviceConnected && oldDeviceConnected)
  {
    pServer->startAdvertising();
    oldDeviceConnected = deviceConnected;
  }

  if (deviceConnected && !oldDeviceConnected)
  {
    oldDeviceConnected = deviceConnected;
  }

/*
  if (houveInterrupt)
  {
    bleComCharacteristics.setValue("START_INTERRUPT");
    bleComCharacteristics.notify();
  }
*/

  if (comando == TESTEPWM_CMD){
    testeVelPWM(velocidade);
  }

  if (comando == PARAR_CMD)
  {
    pararMotor();
  }

  if (comando == LED_CMD)
  {
    //piscaLed();
    //digitalWrite(LED_ONBOARD, HIGH);
  	delay(1000);
    //digitalWrite(LED_ONBOARD, LOW);
  	delay(1000);

  }

  if (comando == STRAT1_CMD)
  {
    busca();
  }

  if (comando == FRENTE_CMD)
  {
    //Serial.println("comando Frente");
    andarFrente();
  }

  if (comando == TRAS_CMD)
  {
    andarTras();
  }

  if(comando == TESTEPWMS_CMD){
    testePWMS();
  }

  if(comando == ARCO_CMD){
    arco();
  }

  if(comando == TOQUINHO_CMD){
    toquinho();
  }

  if(comando == DISTMOTOR_CMD){
    testeDistanciaMotor();
  }

  if(comando == FRENTELINHA_CMD){
    frenteLinha();
  }

  if(comando == MISSIL_LINHA_CMD){
    missilLinha();
  }

  if(comando == MISSIL_CMD){
    missil();
  }
}
