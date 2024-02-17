#include "medusaSENS.h"

void configLinha(){
    analogReadResolution(12);       /*!< Resolução de 12 bits (0 - 4095) */
    analogSetWidth(12);
    analogSetAttenuation(ADC_11db); /*!< Resolução de 12 bits (0 - 4095) */
    adcAttachPin(SENSOR_LINHA_ESQ);      /*!< Atribui ADC aos pinos           */
    adcAttachPin(SENSOR_LINHA_DIR);
    adcAttachPin(SENSOR_LINHA_CENT_ESQ);
    adcAttachPin(SENSOR_LINHA_CENT_DIR);
    adcAttachPin(SENSOR_CORRENTE_ESQ);
    adcAttachPin(SENSOR_CORRENTE_DIR);

    Serial.println("ADC configurado - SUCESSO");
}

bool configGpio(){
  
    //!!VERIFICAR SE SENSOR É BANNER OU PEPPER!!
    //ALTERAR PULLUP E PULLDOWN
    //PINOS 34,35,36 E 39 NAO TEM PULLUP/PULLDOWN

    /**
    * @brief Configuração GPIO36 
    * _SD1 Sensor de distância 
    *
    */
    gpio_config_t gpio36;
    gpio36.pin_bit_mask = (1ULL << GPIO_NUM_36); /*!< Atribui mask GPIO36                 */
    gpio36.mode = GPIO_MODE_INPUT;               /*!< Seta modo GPIO como input           */
    gpio36.pull_up_en = GPIO_PULLUP_DISABLE;     /*!< Desliga GPIO pull-up                */
    gpio36.pull_down_en = GPIO_PULLDOWN_ENABLE;  /*!< Liga GPIO pull-down                 */
    gpio36.intr_type = GPIO_INTR_DISABLE;        /*!< Desabilita Interrupção GPIO         */
    gpio_config(&gpio36);                        /*!< Configuração final GPIO por ponteiro*/

    if(gpio_config(&gpio36) == ESP_ERR_INVALID_ARG){
        return false;
    }

    /**
    * @brief Configuração GPIO35 
    * _SD2 Sensor de distância 
    *
    */
    gpio_config_t gpio35;
    gpio35.pin_bit_mask = (1ULL << GPIO_NUM_35); /*!< Atribui mask GPIO35                 */
    gpio35.mode = GPIO_MODE_INPUT;               /*!< Seta modo GPIO como input           */
    gpio35.pull_up_en = GPIO_PULLUP_DISABLE;     /*!< Desliga GPIO pull-up                */
    gpio35.pull_down_en = GPIO_PULLDOWN_ENABLE;  /*!< Liga GPIO pull-down                 */
    gpio35.intr_type = GPIO_INTR_DISABLE;        /*!< Desabilita Interrupção GPIO         */
    gpio_config(&gpio35);                        /*!< Configuração final GPIO por ponteiro*/

    if(gpio_config(&gpio35) == ESP_ERR_INVALID_ARG){
        return false;
    }

    /**
    * @brief Configuração GPIO32 
    * _SD3 Sensor de distância 
    *
    */
    gpio_config_t gpio32;
    gpio32.pin_bit_mask = (1ULL << GPIO_NUM_32); /*!< Atribui mask GPIO32                 */
    gpio32.mode = GPIO_MODE_INPUT;               /*!< Seta modo GPIO como input           */
    gpio32.pull_up_en = GPIO_PULLUP_ENABLE;     /*!< Desliga GPIO pull-up                */
    gpio32.pull_down_en = GPIO_PULLDOWN_DISABLE;  /*!< Liga GPIO pull-down                 */
    gpio32.intr_type = GPIO_INTR_DISABLE;        /*!< Desabilita Interrupção GPIO         */
    gpio_config(&gpio32);                        /*!< Configuração final GPIO por ponteiro*/

    if(gpio_config(&gpio32) == ESP_ERR_INVALID_ARG){
        return false;
    }

    /**
    * @brief Configuração GPIO33 
    * _SD4 Sensor de distância 
    *
    */
    gpio_config_t gpio33;
    gpio33.pin_bit_mask = (1ULL << GPIO_NUM_33); /*!< Atribui mask GPIO33                 */
    gpio33.mode = GPIO_MODE_INPUT;               /*!< Seta modo GPIO como input           */
    gpio33.pull_up_en = GPIO_PULLUP_ENABLE;     /*!< Desliga GPIO pull-up                */
    gpio33.pull_down_en = GPIO_PULLDOWN_DISABLE;  /*!< Liga GPIO pull-down                 */
    gpio33.intr_type = GPIO_INTR_DISABLE;        /*!< Desabilita Interrupção GPIO         */
    gpio_config(&gpio33);                        /*!< Configuração final GPIO por ponteiro*/

    if(gpio_config(&gpio33) == ESP_ERR_INVALID_ARG){
        return false;
    }

        /**
    * @brief Configuração GPIO25 
    * _SD5 Sensor de distância / BANDEIRA
    *
    */
    gpio_config_t gpio25;
    gpio25.pin_bit_mask = (1ULL << GPIO_NUM_25); /*!< Atribui mask GPIO25                 */
    gpio25.mode = GPIO_MODE_INPUT;               /*!< Seta modo GPIO como input           */
    gpio25.pull_up_en = GPIO_PULLUP_DISABLE;     /*!< Desliga GPIO pull-up                */
    gpio25.pull_down_en = GPIO_PULLDOWN_ENABLE;  /*!< Liga GPIO pull-down                 */
    gpio25.intr_type = GPIO_INTR_DISABLE;        /*!< Desabilita Interrupção GPIO         */
    gpio_config(&gpio25);                        /*!< Configuração final GPIO por ponteiro*/

    if(gpio_config(&gpio25) == ESP_ERR_INVALID_ARG){
        return false;
    }

    /**
    * @brief Configuração GPIO26 
    * _SD6 Sensor de distância 
    *
    */
    gpio_config_t gpio26;
    gpio26.pin_bit_mask = (1ULL << GPIO_NUM_26); /*!< Atribui mask GPIO26                 */
    gpio26.mode = GPIO_MODE_INPUT;               /*!< Seta modo GPIO como input           */
    gpio26.pull_up_en = GPIO_PULLUP_ENABLE;     /*!< Desliga GPIO pull-up                */
    gpio26.pull_down_en = GPIO_PULLDOWN_DISABLE;  /*!< Liga GPIO pull-down                 */
    gpio26.intr_type = GPIO_INTR_DISABLE;        /*!< Desabilita Interrupção GPIO         */
    gpio_config(&gpio26);                        /*!< Configuração final GPIO por ponteiro*/

    if(gpio_config(&gpio26) == ESP_ERR_INVALID_ARG){
        return false;
    }

        /**
    * @brief Configuração GPIO27 
    * _SD7 Sensor de distância 
    *
    */
    gpio_config_t gpio27;
    gpio27.pin_bit_mask = (1ULL << GPIO_NUM_27); /*!< Atribui mask GPIO27                 */
    gpio27.mode = GPIO_MODE_INPUT;               /*!< Seta modo GPIO como input           */
    gpio27.pull_up_en = GPIO_PULLUP_ENABLE;     /*!< Desliga GPIO pull-up                */
    gpio27.pull_down_en = GPIO_PULLDOWN_DISABLE;  /*!< Liga GPIO pull-down                 */
    gpio27.intr_type = GPIO_INTR_DISABLE;        /*!< Desabilita Interrupção GPIO         */
    gpio_config(&gpio27);                        /*!< Configuração final GPIO por ponteiro*/

    if(gpio_config(&gpio27) == ESP_ERR_INVALID_ARG){
        return false;
    }

    /**
    * @brief Configuração GPIO14 
    * _SD8 Sensor de distância 
    *
    */
    gpio_config_t gpio14;
    gpio14.pin_bit_mask = (1ULL << GPIO_NUM_14); /*!< Atribui mask GPIO14                 */
    gpio14.mode = GPIO_MODE_INPUT;               /*!< Seta modo GPIO como input           */
    gpio14.pull_up_en = GPIO_PULLUP_ENABLE;     /*!< Desliga GPIO pull-up                */
    gpio14.pull_down_en = GPIO_PULLDOWN_DISABLE;  /*!< Liga GPIO pull-down                 */
    gpio14.intr_type = GPIO_INTR_DISABLE;        /*!< Desabilita Interrupção GPIO         */
    gpio_config(&gpio14);                        /*!< Configuração final GPIO por ponteiro*/

    if(gpio_config(&gpio14) == ESP_ERR_INVALID_ARG){
        return false;
    }


    /**
    * @brief Configuração gpio15
    * Input módulo Start
    * 
    */
   
    gpio_config_t gpio15;
    gpio15.pin_bit_mask = (1ULL << GPIO_NUM_15); /*!< Atribui mask gpio15                 */
    gpio15.mode = GPIO_MODE_INPUT;              /*!< seta modo GPIO como output          */
    gpio15.pull_up_en = GPIO_PULLUP_DISABLE;     /*!< DesLiga GPIO pull-up                */
    gpio15.pull_down_en = GPIO_PULLDOWN_ENABLE; /*!< Desliga GPIO pull-down              */
    //gpio15.intr_type = GPIO_INTR_NEGEDGE;
    gpio15.intr_type = GPIO_INTR_DISABLE;        /*!< Desabilita Interrupção GPIO         */
    gpio_config(&gpio15);                        /*!< Configuração final GPIO por ponteiro*/

    if(gpio_config(&gpio15) == ESP_ERR_INVALID_ARG){
        return false;
   }

    //pinMode(15, INPUT_PULLDOWN);
    //pinMode(2, OUTPUT);

    Serial.println("GPIO configurados - SUCESSO");
    return true;
}