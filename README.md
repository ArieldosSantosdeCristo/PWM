# PWM

Controle de Servo Motor com Raspberry Pi Pico

Este projeto controla um servo motor utilizando a Raspberry Pi Pico por meio do PWM. O código movimenta o servo entre 0° e 180° de forma suave e contínua.

📌 Funcionalidades
Configuração do PWM para controle do servo.
Movimentação suave e progressiva do servo entre 0° e 180°.
Definição de três posições iniciais antes do movimento contínuo.

🛠 Requisitos
Raspberry Pi Pico
Servo motor compatível com PWM
Ambiente de desenvolvimento compatível com C/C++

🚀 Como executar
Compile e carregue o código na Raspberry Pi Pico.
Conecte o servo motor ao GPIO 22.
O servo se moverá inicialmente para 180° → 90° → 0°.
Após isso, iniciará um movimento oscilatório contínuo entre 0° e 180°.

Video: https://drive.google.com/file/d/152Q_ysI2kPHuONgFpUiBveq_Q8NXVBQ6/view?usp=sharing