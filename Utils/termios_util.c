#include "termios_util.h"

char binary_system[9] = "00000001";
float motor_temperature = 0;

void set_termios(struct termios *prev) {
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, prev);
    new_termios = *prev;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void restore_termios(struct termios *prev) {
    tcsetattr(STDIN_FILENO, TCSANOW, prev);
}

void le_teclado() {
    struct termios prev_termios;
    set_termios(&prev_termios);

    while (1) {
        char tecla;
        char buffer[1];
        motor_temperature = 60; // Temperatura do motor
        if (read(STDIN_FILENO, buffer, 1) > 0) {
            tecla = buffer[0];
            if (tecla == 'v' || tecla == 'V') {
                binary_system[0] = (binary_system[0] == '0') ? '1' : '0'; //Vidro motorista
            } else if (tecla == 'b' || tecla == 'B') {
                binary_system[1] = (binary_system[1] == '0') ? '1' : '0'; //Vidro passageiro
            } else if (tecla == 'n' || tecla == 'N') {
                binary_system[2] = (binary_system[2] == '0') ? '1' : '0'; //Trava porta motorista 
            } else if (tecla == 'm' || tecla == 'M') {
                binary_system[3] = (binary_system[3] == '0') ? '1' : '0'; //Trava porta passageiro
            } else if (tecla == 'l' || tecla == 'L') {
                binary_system[4] = (binary_system[4] == '0') ? '1' : '0'; //Faróis dianteiros
            } else if (tecla == 'k' || tecla == 'K') {
                binary_system[5] = (binary_system[5] == '0') ? '1' : '0'; //ABS funcionando roda direita
            } else if (tecla == 'j' || tecla == 'J') {
                binary_system[6] = (binary_system[6] == '0') ? '1' : '0'; //ABS funcionando roda esquerda
            } else if (tecla == 'h' || tecla == 'H') {
                binary_system[7] = (binary_system[7] == '0') ? '1' : '0'; //Injeção funcionando 
            }
        }
    }
    restore_termios(&prev_termios);
}
