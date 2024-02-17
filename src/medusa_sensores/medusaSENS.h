#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef MEDUSA_SENS_H
#define MEDUSA_SENS_H

#define SENSOR_CORRENTE_ESQ GPIO_NUM_16 //ISL
#define SENSOR_CORRENTE_DIR GPIO_NUM_17 //ISR

/*
#define SENSOR_LINHA_ESQ GPIO_NUM_13 //SL1
#define SENSOR_LINHA_CENT_ESQ GPIO_NUM_39 //SL2
#define SENSOR_LINHA_CENT_DIR GPIO_NUM_12 //SL3
#define SENSOR_LINHA_DIR GPIO_NUM_38 //SL4
*/

#define SENSOR_LINHA_ESQ GPIO_NUM_27 //SL0
#define SENSOR_LINHA_DIR GPIO_NUM_14 //SL1
#define SENSOR_LINHA_CENT_DIR GPIO_NUM_4 //SL2
#define SENSOR_LINHA_CENT_ESQ GPIO_NUM_36 //SL3

//USAR 3,4,6,7,8

/*
#define SENSOR_LAT_DIR GPIO_NUM_34  //_SD1 ok
#define SENSOR_FRONT_DIR GPIO_NUM_35  //_SD2 ok
#define SENSOR_LAT_ESQ  GPIO_NUM_32  //_SD3 ok
#define SENSOR_FRONT_ESQ GPIO_NUM_33 //_SD4 ok
#define SENSOR_CENT_ESQ GPIO_NUM_25  //_SD5 E BANDEIRA ok
#define SENSOR_CENT_DIR GPIO_NUM_26  //_SD6 ok
#define SENSOR_LAT_ESQ2  GPIO_NUM_27  //_SD7
#define SENSOR_FRONT_ESQ2 GPIO_NUM_14 //_SD8
*/

#define SENSOR_LAT_DIR  GPIO_NUM_39  //SD0
#define SENSOR_FRONT_DIR GPIO_NUM_34 //SD1
#define SENSOR_CENT_ESQ GPIO_NUM_35  //SD2
#define SENSOR_FRONT_ESQ  GPIO_NUM_32  //SD3
#define SENSOR_LAT_ESQ GPIO_NUM_33 //SD4


//#define LED_ONBOARD 2

#define START GPIO_NUM_15


/**
 * @brief Configuração ADC sonic
 *
 *        Configura resolução do ADC, largura, ciclos por amostra, quantidade de amostra,
 *        atenuação, pinos do ADC
 * @return
 *     VOID
 *
 */
void configLinha();

/**
 * @brief Configuração ADC sonic
 *
 *        Configura resolução do ADC, largura, ciclos por amostra, quantidade de amostra,
 *        atenuação, pinos do ADC
 * @return
 *     VOID
 *
 */
bool configGpio();

#endif

#ifdef __cplusplus
}
#endif