#include "termios_util.h"

char binary_system[13] = "000000011100"; // Airbags e Injeção começam ativados
float motor_temperature = 0;

void set_termios(struct termios *prev)
{
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, prev);
    new_termios = *prev;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void restore_termios(struct termios *prev)
{
    tcsetattr(STDIN_FILENO, TCSANOW, prev);
}

void le_teclado()
{
    struct termios prev_termios;
    set_termios(&prev_termios);

    while (1)
    {
        usleep(16); // delay de 16us pelo fio e 1us de aquisicao do sensor e 5us do controlador
        char tecla;
        char buffer[1];
        motor_temperature = 60; // Temperatura do motor

        if (read(STDIN_FILENO, buffer, 1) > 0)
        {
            tecla = buffer[0];
            if (tecla == 'v' || tecla == 'V')
            {
                binary_system[0] = (binary_system[0] == '0') ? '1' : '0'; // Vidro motorista
            }
            else if (tecla == 'b' || tecla == 'B')
            {
                binary_system[1] = (binary_system[1] == '0') ? '1' : '0'; // Vidro passageiro
            }
            else if (tecla == 'n' || tecla == 'N')
            {
                binary_system[2] = (binary_system[2] == '0') ? '1' : '0'; // Trava porta motorista
            }
            else if (tecla == 'm' || tecla == 'M')
            {
                binary_system[3] = (binary_system[3] == '0') ? '1' : '0'; // Trava porta passageiro
            }
            else if (tecla == 'l' || tecla == 'L')
            {
                binary_system[4] = (binary_system[4] == '0') ? '1' : '0'; // Faróis dianteiros
            }
            else if (tecla == 'k' || tecla == 'K')
            {
                binary_system[5] = (binary_system[5] == '0') ? '1' : '0'; // ABS roda direita
            }
            else if (tecla == 'j' || tecla == 'J')
            {
                binary_system[6] = (binary_system[6] == '0') ? '1' : '0'; // ABS roda esquerda
            }
            else if (tecla == 'h' || tecla == 'H')
            {
                binary_system[7] = (binary_system[7] == '0') ? '1' : '0'; // Injeção
            }
            else if (tecla == 'g' || tecla == 'G')
            {
                binary_system[8] = (binary_system[8] == '0') ? '1' : '0'; // AirBag motorista
            }
            else if (tecla == 'f' || tecla == 'F')
            {
                binary_system[9] = (binary_system[9] == '0') ? '1' : '0'; // AirBag passageiro
            }
            else if (tecla == 'd' || tecla == 'D')
            {
                binary_system[10] = (binary_system[10] == '0') ? '1' : '0'; // Cinto motorista
            }
            else if (tecla == 's' || tecla == 'S')
            {
                binary_system[11] = (binary_system[11] == '0') ? '1' : '0'; // Cinto passageiro
            }
            else if (tecla == '0') // Altera todos sensores
            {
                binary_system[0] = (binary_system[0] == '0') ? '1' : '0';
                binary_system[1] = (binary_system[1] == '0') ? '1' : '0';
                binary_system[2] = (binary_system[2] == '0') ? '1' : '0';
                binary_system[3] = (binary_system[3] == '0') ? '1' : '0';
                binary_system[4] = (binary_system[4] == '0') ? '1' : '0';
                binary_system[5] = (binary_system[5] == '0') ? '1' : '0';
                binary_system[6] = (binary_system[6] == '0') ? '1' : '0';
                binary_system[7] = (binary_system[7] == '0') ? '1' : '0';
                binary_system[8] = (binary_system[8] == '0') ? '1' : '0';
                binary_system[9] = (binary_system[9] == '0') ? '1' : '0';
                binary_system[10] = (binary_system[10] == '0') ? '1' : '0';
                binary_system[11] = (binary_system[11] == '0') ? '1' : '0';
            }
        }
    }
    restore_termios(&prev_termios);
}