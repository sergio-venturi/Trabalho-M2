#include <stdio.h>
#include <termios.h>
#include <unistd.h>

char binary_lvtsystem[6] = "00000";

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

        if (read(STDIN_FILENO, buffer, 1) > 0) {
            tecla = buffer[0];

            if (tecla == 'v' || tecla == 'V') {
                binary_lvtsystem[0] = (binary_lvtsystem[0] == '0') ? '1' : '0';
            } else if (tecla == 'b' || tecla == 'B') {
                binary_lvtsystem[1] = (binary_lvtsystem[1] == '0') ? '1' : '0';
            } else if (tecla == 'n' || tecla == 'N') {
                binary_lvtsystem[2] = (binary_lvtsystem[2] == '0') ? '1' : '0';
            } else if (tecla == 'm' || tecla == 'M') {
                binary_lvtsystem[3] = (binary_lvtsystem[3] == '0') ? '1' : '0';
            } else if (tecla == 'l' || tecla == 'L') {
                binary_lvtsystem[4] = (binary_lvtsystem[4] == '0') ? '1' : '0';
            }
        }
    }

    restore_termios(&prev_termios);
}

int lvt_system() {
    le_teclado();
    return 0;
}
