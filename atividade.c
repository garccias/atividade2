#include <stdio.h>
#include "pico/stdlib.h"
#include "funcoes.c"
#include "pico/bootrom.h"
#include "pico/time.h"

#define botaoA_pin 5 // Butão A

// funções de interrupção por gpio e timer
static void gpio_irq_handler(uint gpio, uint32_t events);

int64_t turn_off_Blue(alarm_id_t id, void *user_data);
int64_t turn_off_Green(alarm_id_t id, void *user_data);
int64_t turn_off_Red(alarm_id_t id, void *user_data);

const uint rgbPin[3] = {13, 12, 11}; 
const uint reset_pin = 22;           

// Variáveis globais
bool reset = false;
static volatile uint32_t last_time = 0;
bool ledOff = 1;
bool buttonPres = 0;
int i = 0;

int main()
{
    stdio_init_all();

    initLED(rgbPin);
    initButton(botaoA_pin);
    initButton(reset_pin);
    gpio_set_irq_enabled_with_callback(botaoA_pin, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(reset_pin, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true)
    {
        if (!ledOff && buttonPres)
        {
            // Utiliza a variável para não repetir a condição antes dos leds desligarem
            buttonPres = false;
            for (size_t i = 0; i < 3; i++)
            {
                gpio_put(rgbPin[i], 1);
            }

            add_alarm_in_ms(3e3, turn_off_Green, NULL, false);
            add_alarm_in_ms(6e3, turn_off_Blue, NULL, false);
            add_alarm_in_ms(9e3, turn_off_Red, NULL, false);
        }

        else if (reset) // Quando apertar o botão do joystick entra em modo bootloader
        {
            printf("HABILITANDO O MODO GRAVAÇÃO");
            reset_usb_boot(0, 0);
        }
        sleep_ms(10);
    }
}

void gpio_irq_handler(uint gpio, uint32_t events)
{
    uint32_t current_time = to_ms_since_boot(get_absolute_time()); 
    if (gpio == botaoA_pin && ledOff && current_time - last_time > 2e2)
    {
        ledOff = false;
        buttonPres = true;
        last_time = current_time;
    }
    else if (gpio == reset_pin)
    {
        reset = 1;
    }
}

int64_t turn_off_Green(alarm_id_t id, void *user_data)
{
    // Desliga o LED configurando o pino 11 para nível baixo.
    gpio_put(rgbPin[2], false);
    printf("Passou 3 segundos\n");
    // Retorna 0 para indicar que o alarme não deve se repetir.
    return 0;
}

int64_t turn_off_Blue(alarm_id_t id, void *user_data)
{
    gpio_put(rgbPin[1], false);
    printf("Passou 6 segundos\n");
    return 0;
}

int64_t turn_off_Red(alarm_id_t id, void *user_data)
{
    gpio_put(rgbPin[0], false);
    printf("Passou 9 segundos\n");
    ledOff = true;
    return 0;
}