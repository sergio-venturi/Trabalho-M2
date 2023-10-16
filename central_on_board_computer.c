#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <termios.h>
#include <fcntl.h>
#include <stdbool.h>
#include "lvt_system.h"

//gcc -o central Systems/lvt_system.c central_on_board_computer.c -lpthread
// ./central

extern char binary_lvtsystem[6]; //Variável para a leitura do código binário LVT

void data_reading(){
    while(1){
        printf("%s\n", binary_lvtsystem);
    }
}

int main(int argc, char *argv[]) {
    pthread_t thread_lvtsystem, thread_data_reading;

    // Cria a thread
    pthread_create(&thread_lvtsystem, NULL, (void *)lvt_system, NULL);
    pthread_create(&thread_data_reading, NULL, (void *)data_reading, NULL);

    // Conclusão da thread
    pthread_join(thread_lvtsystem, NULL);
    pthread_join(thread_data_reading, NULL);

    return 0;
}
