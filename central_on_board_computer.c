#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Utils/termios_util.h"
#include "Systems/lvt_system.h"
#include "Systems/brake_system.h"
#include "Systems/motor_system.h"
#include "Systems/life_support_equipment_system.h"

//gcc -o central Systems/lvt_system.c Systems/brake_system.c Systems/motor_system.c Systems/life_support_equipment_system.c Utils/termios_util.c central_on_board_computer.c -lpthread
// ./central

extern float motor_temperature;     //Variável para a leitura da temperatura do Motor
extern char binary_lvtsystem[6];    //Variável para a leitura do código binário LVT
extern char binary_brake_system[3]; //Variável para a leitura do código binário Freio
extern char binary_motor_system[2]; //Variável para a leitura do código binário Motor
extern char binary_life_support_system[5]; //Variável para a leitura do código binário LSE

void data_reading(){
    le_teclado();
}
void data_print(){
    while(1){
        printf("%s-", binary_lvtsystem);
        printf("%s-", binary_brake_system);
        printf("%s-", binary_motor_system);
        printf("%s-", binary_life_support_system);
        printf("%0.2f\n", motor_temperature);

        usleep(5000);
        system("clear");
    }
}

int main(int argc, char *argv[]) {
    pthread_t thread_lvtsystem,thread_brake_system, thread_motor_system, 
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
