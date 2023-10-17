#include "../Utils/termios_util.h"
#include <string.h>

extern char binary_system[8]; 
char binary_motor_system[2] = "0";  //Injeção Ligada - Desligada
extern float motor_temperature;     //Variável para a leitura da temperatura do Motor

int motor_system() {
    while (1)
    {
        memcpy(binary_motor_system, &binary_system[7], 2);
        usleep(1000);/* code */
    }
    
    return 0;
}
