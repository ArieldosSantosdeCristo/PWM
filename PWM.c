#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PINO_SERVO 22 // Pino do servo motor (GPIO 22)
#define PINO_LED   12 // Pino do LED RGB (GPIO 12 Azul)

// Definições do PWM para 50Hz (período de 20ms)
const uint16_t PERIODO_PWM = 20000;
const float DIVISOR_PWM = 125.0;

// Posições do servo motor em microssegundos
const uint16_t PULSO_180_GRAUS = 2400;
const uint16_t PULSO_90_GRAUS  = 1470;
const uint16_t PULSO_0_GRAUS   = 500;

// Configurações da movimentação suave
const uint16_t INCREMENTO_PASSO = 5;
const uint16_t ATRASO_PASSO = 10;

uint16_t posicao_servo = PULSO_0_GRAUS;
bool aumentando = true;

// Função para configurar o PWM
void configurar_pwm(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    pwm_set_clkdiv(slice, DIVISOR_PWM);
    pwm_set_wrap(slice, PERIODO_PWM);
    pwm_set_gpio_level(gpio, 0);
    pwm_set_enabled(slice, true);
}

// Função para ajustar a posição do servo e a intensidade do LED
void ajustar_servo_e_led(uint16_t largura_pulso) {
    pwm_set_gpio_level(PINO_SERVO, largura_pulso);
    pwm_set_gpio_level(PINO_LED, (largura_pulso - PULSO_0_GRAUS) * 10);
}

// Movimentação contínua e suave entre 0° e 180°
void movimentar_servo_suavemente() {
    while (true) {
        ajustar_servo_e_led(posicao_servo);
        sleep_ms(ATRASO_PASSO);
        
        posicao_servo += aumentando ? INCREMENTO_PASSO : -INCREMENTO_PASSO;
        
        if (posicao_servo >= PULSO_180_GRAUS || posicao_servo <= PULSO_0_GRAUS) {
            aumentando = !aumentando;
        }
    }
}

int main() {
    stdio_init_all();
    configurar_pwm(PINO_SERVO);
    configurar_pwm(PINO_LED);

    uint16_t posicoes_iniciais[] = {PULSO_180_GRAUS, PULSO_90_GRAUS, PULSO_0_GRAUS};
    for (int i = 0; i < 3; i++) {
        ajustar_servo_e_led(posicoes_iniciais[i]);
        sleep_ms(5000);
    }

    movimentar_servo_suavemente();
    return 0;
}
