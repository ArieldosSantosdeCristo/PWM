#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22
#define LED_PIN 12
#define PWM_FREQ 50
#define CLOCK_FREQ 125000000

void set_servo_angle(uint slice_num, uint channel, uint32_t pulse_width_us) {
    uint32_t wrap_value = (CLOCK_FREQ / PWM_FREQ) - 1;
    
    uint32_t duty = (pulse_width_us * wrap_value) / 20000;
    
    pwm_set_chan_level(slice_num, channel, duty);
    pwm_set_enabled(slice_num, true); // Garantir que o PWM esteja ativado
}

int main() {
    stdio_init_all();

    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    uint channel = pwm_gpio_to_channel(SERVO_PIN);

    uint32_t wrap_value = (CLOCK_FREQ / PWM_FREQ) - 1;
    pwm_set_wrap(slice_num, wrap_value);
    pwm_set_clkdiv(slice_num, 64.0); // Redução da frequência para estabilidade
    pwm_set_enabled(slice_num, true);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Definir ângulos fixos
    set_servo_angle(slice_num, channel, 2400); // 180°
    gpio_put(LED_PIN, 1);
    sleep_ms(5000);

    set_servo_angle(slice_num, channel, 1470); // 90°
    sleep_ms(5000);

    set_servo_angle(slice_num, channel, 500); // 0°
    gpio_put(LED_PIN, 0);
    sleep_ms(5000);

    // Movimentação periódica entre 0° e 180° com incremento suave
    while (1) {
        for (uint32_t pulse = 500; pulse <= 2400; pulse += 5) {
            set_servo_angle(slice_num, channel, pulse);
            sleep_ms(10); // Ajuste de atraso de 10ms ao atingir 180°
        }
        sleep_ms(1000); // Pequena pausa no extremo 0°
        for (uint32_t pulse = 2400; pulse >= 500; pulse -= 5) {
            set_servo_angle(slice_num, channel, pulse);
            sleep_ms(20); // Ajuste para um movimento mais suave
        }
        sleep_ms(1000); // Pequena pausa no extremo 0°
    }
}
