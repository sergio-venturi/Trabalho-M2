#include "../Utils/termios_util.h"
#include <string.h>

extern char binary_system[13]; 
char binary_life_support_system[5] = "0000";

int life_support_equipment_system() {
    while (1)
    {
        memcpy(binary_life_support_system, &binary_system[8], 4);
        usleep(1000);/* code */
    }
    
    return 0;
}
