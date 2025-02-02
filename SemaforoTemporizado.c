#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h" //Inclui a biblioteca para gerenciamento de temporizadores de hardware.

#define LED_PIN_RED 11
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 13

//Funcao para inicializar os pinos
void InicizalizaGPIO(){
    stdio_init_all();    

    //Inicializa pinos dos leds
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_put(LED_PIN_RED, 1);
    
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    gpio_put(LED_PIN_YELLOW, 0);

    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_put(LED_PIN_GREEN, 0);
}

bool repeating_timer_callback(struct repeating_timer *t){
  if(gpio_get(LED_PIN_RED)==1 && gpio_get(LED_PIN_YELLOW)==0 && gpio_get(LED_PIN_GREEN)==0){
    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_YELLOW, 1);
  }else if(gpio_get(LED_PIN_RED)==0 && gpio_get(LED_PIN_YELLOW)==1 && gpio_get(LED_PIN_GREEN)==0){
    gpio_put(LED_PIN_YELLOW, 0);
    gpio_put(LED_PIN_GREEN, 1);
  }else if(gpio_get(LED_PIN_RED)==0 && gpio_get(LED_PIN_YELLOW)==0 && gpio_get(LED_PIN_GREEN)==1){
    gpio_put(LED_PIN_GREEN, 0);
    gpio_put(LED_PIN_RED, 1);
  }
  return true;
}

int main(){
    InicizalizaGPIO();
    
    //Declaração de uma estrutura de temporizador de repetição.
    //Esta estrutura armazenará informações sobre o temporizador configurado.
    struct repeating_timer timer;
    //Configura o temporizador para chamar a função de callback a cada 3 segundos.
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while(true){
        if(gpio_get(LED_PIN_RED)==1){
            printf("PARADA OBRIGATÓRIA!!!");
        }else if(gpio_get(LED_PIN_YELLOW)==1){
            printf("SINAL AMARELO, MUITA ATENÇÃO!!!");
        }else if(gpio_get(LED_PIN_GREEN)==1){
            printf("SINAL ABERTO, PROSSIGA!");
        }
        sleep_ms(1000);
    }
  return 0;
}