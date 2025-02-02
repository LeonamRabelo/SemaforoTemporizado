#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h" //Inclui a biblioteca para gerenciamento de temporizadores de hardware.

//Definição dos pinos dos leds
#define LED_PIN_RED 11
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 13

//Funcao para inicializar os pinos e comunicação
void InicializaGPIO(){
    stdio_init_all();     //Inicializa a comunicação serial, permitindo o uso de funções como printf.

    //Inicializa pinos dos leds
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_put(LED_PIN_RED, 1);   //Inicializo com apenas o led vermelho ligado, como pedido na tarefas
    
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    gpio_put(LED_PIN_YELLOW, 0);

    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_put(LED_PIN_GREEN, 0);
}

//Funcao a ser chamada no temporizador
bool repeating_timer_callback(struct repeating_timer *t){
    //Se apenas o led vermelho estiver ativo, desativa ele e passa a ativar o amarelo
    if(gpio_get(LED_PIN_RED)==1 && gpio_get(LED_PIN_YELLOW)==0 && gpio_get(LED_PIN_GREEN)==0){
    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_YELLOW, 1);
    }
    //Se apenas o led amarelo estiver ativo, desativa ele e passa a ativar o verde
    else if(gpio_get(LED_PIN_RED)==0 && gpio_get(LED_PIN_YELLOW)==1 && gpio_get(LED_PIN_GREEN)==0){
    gpio_put(LED_PIN_YELLOW, 0);
    gpio_put(LED_PIN_GREEN, 1);
    }
    //Se apenas o led verde estiver ativo, desativa ele e passa a ativar o vermelho
    else if(gpio_get(LED_PIN_RED)==0 && gpio_get(LED_PIN_YELLOW)==0 && gpio_get(LED_PIN_GREEN)==1){
    gpio_put(LED_PIN_GREEN, 0);
    gpio_put(LED_PIN_RED, 1);
    }
return true;
}

int main(){
    InicializaGPIO();
    
    //Declaração de uma estrutura de temporizador de repetição.
    //Esta estrutura armazenará informações sobre o temporizador configurado.
    struct repeating_timer timer;
    //Configura o temporizador para chamar a função de callback a cada 3 segundos.
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    //Laço de repetição principal
    while(true){
        if(gpio_get(LED_PIN_RED)==1){   //Verifica se o led vermelho está aceso
            printf("PARADA OBRIGATÓRIA!!!\n");
        }else if(gpio_get(LED_PIN_YELLOW)==1){  //Verifica se o led amarelo está aceso
            printf("SINAL AMARELO, MUITA ATENÇÃO!!!\n");
        }else if(gpio_get(LED_PIN_GREEN)==1){   //Verifica se o led verde está aceso
            printf("SINAL ABERTO, PROSSIGA!\n");
        }
        sleep_ms(1000); //Intervalo de 1 segundo entre cada verificação para imprimir os alertas
    }
  return 0;
}