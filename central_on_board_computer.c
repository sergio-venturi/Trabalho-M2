#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "Utils/termios_util.h"
#include "Systems/lvt_system.h"
#include "Systems/brake_system.h"
#include "Systems/motor_system.h"
#include "Systems/life_support_equipment_system.h"

// gcc -o central Systems/lvt_system.c Systems/brake_system.c Systems/motor_system.c Systems/life_support_equipment_system.c Utils/termios_util.c central_on_board_computer.c -lpthread
//  ./central

// --Comandos--
// v = Vidro Motorista
// b = Vidro Passageiro
// n = Trava Porta Motorista
// m = Trava Porta Passageiro
// l = Faróis Dianteiros
// k = ABS Roda Direita
// j = ABS Roda Esquerda
// h = Injeção
// g = AirBag Motorista
// f = AirBag Passageiro
// d = Cinto Motorista
// s = Cinto Passageiro

extern float motor_temperature;            // Variável para a leitura da temperatura do Motor
extern float velocidade;
extern char binary_lvtsystem[6];           // Variável para a leitura do código binário LVT
extern char binary_brake_system[3];        // Variável para a leitura do código binário Freio
extern char binary_motor_system[2];        // Variável para a leitura do código binário Motor
extern char binary_life_support_system[5]; // Variável para a leitura do código binário LSE

void printBinaryField(const char *name, const char *binary)
{
    printf("%s: ", name);

    if (binary[0] == '0')
    {
        printf("\033[31mDESATIVADO \033[0m"); // Vermelho para desativado
    }
    else
    {
        printf("\033[32mATIVADO \033[0m"); // Verde para ativado
    }

    printf("\n");
}

void update_motor_temperature() {
    if (velocidade >= 60.0) {
        motor_temperature += 0.1; // Aumentar a temperatura
    } else {
        motor_temperature -= 0.1; // Diminuir a temperatura
    }
    
    // Limitar a temperatura entre 60 e 100 graus
    if (motor_temperature < 60.0) {
        motor_temperature = 60.0;
    } else if (motor_temperature > 100.0) {
        motor_temperature = 100.0;
    }
}

struct timeval start_time, end_time; // variaveis para calcular o tempo

void data_reading()
{
    gettimeofday(&start_time, NULL); // inicia calculo do tempo
    le_teclado();
}

void data_print()
{

    while (1)
    {
        gettimeofday(&end_time, NULL); // finaliza calculo do tempo
        long seconds = end_time.tv_sec - start_time.tv_sec;
        long microseconds = end_time.tv_usec - start_time.tv_usec;
        double elapsed = seconds + microseconds / 1e6;
        printf("Tempo total gasto: %.6f segundos\n", elapsed);

        printBinaryField("(V)Vidro Motorista", binary_lvtsystem);
        printBinaryField("(B)Vidro Passageiro", binary_lvtsystem + 1);
        printBinaryField("(N)Trava porta motorista", binary_lvtsystem + 2);
        printBinaryField("(M)Trava porta passageiro", binary_lvtsystem + 3);
        printBinaryField("(L)Faróis dianteiros", binary_lvtsystem + 4);

        printBinaryField("(K)ABS roda direita", binary_brake_system);
        printBinaryField("(J)ABS roda esquerda", binary_brake_system + 1);

        printBinaryField("(H)Injeção", binary_motor_system);

        printBinaryField("(G)AirBag motorista", binary_life_support_system);
        printBinaryField("(F)AirBag passageiro", binary_life_support_system + 1);
        printBinaryField("(D)Cinto motorista", binary_life_support_system + 2);
        printBinaryField("(S)Cinto passageiro", binary_life_support_system + 3);
        update_motor_temperature(); // Atualizar a temperatura com base na velocidade

        // Imprima a temperatura
        printf("Temperatura do motor: %.2f\n", motor_temperature);
        if (velocidade > 0.0) {
            velocidade -= 0.1;
            }
        printf("( )Velocidade: %.2f\n", velocidade);

        usleep(500000); // 500ms timeout
        system("clear");
    }
}

int main(int argc, char *argv[])
{
    pthread_t thread_lvtsystem, thread_brake_system, thread_motor_system,
        thread_life_support_equipment, thread_data_reading, thread_data_print;

    // Cria as threads
    pthread_create(&thread_lvtsystem, NULL, (void *)lvt_system, NULL);
    pthread_create(&thread_brake_system, NULL, (void *)brake_system, NULL);
    pthread_create(&thread_motor_system, NULL, (void *)motor_system, NULL);
    pthread_create(&thread_life_support_equipment, NULL, (void *)life_support_equipment_system, NULL);
    pthread_create(&thread_data_reading, NULL, (void *)data_reading, NULL);
    pthread_create(&thread_data_print, NULL, (void *)data_print, NULL);

    // Conclusão da thread
    pthread_join(thread_lvtsystem, NULL);
    pthread_join(thread_brake_system, NULL);
    pthread_join(thread_motor_system, NULL);
    pthread_join(thread_life_support_equipment, NULL);
    pthread_join(thread_data_reading, NULL);
    pthread_join(thread_data_print, NULL);

    return 0;
}
