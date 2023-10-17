#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Utils/termios_util.h"
#include "lvt_system.h"
#include "brake_system.h"

//gcc -o central Systems/lvt_system.c Systems/brake_system.c Utils/termios_util.c central_on_board_computer.c -lpthread
// ./central

extern char binary_lvtsystem[6]; //Variável para a leitura do código binário LVT
extern char binary_brake_system[3]; //Variável para a leitura do código binário Freio

void data_reading(){
    while(1){
        le_teclado();
    }
}
void data_print(){
    while(1){
        printf("%s-", binary_lvtsystem);
        printf("%s\n", binary_brake_system);
    }
}

int main(int argc, char *argv[]) {
    pthread_t thread_lvtsystem,thread_brake_system, thread_life_support_equipment, 
    thread_data_reading, thread_data_print;

    // Cria as threads
    pthread_create(&thread_lvtsystem, NULL, (void *)lvt_system, NULL);
    pthread_create(&thread_brake_system, NULL, (void *)brake_system, NULL);
    pthread_create(&thread_data_reading, NULL, (void *)data_reading, NULL);
    pthread_create(&thread_data_print, NULL, (void *)data_print, NULL);


    // Conclusão da thread
    pthread_join(thread_lvtsystem, NULL);
    pthread_join(thread_brake_system, NULL);
    pthread_join(thread_data_reading, NULL);
    pthread_join(thread_data_print, NULL);


    return 0;
}
