#include "../Utils/termios_util.h"
#include <string.h>

char binary_brake_system[3] = "00";
extern char binary_system[13];

int brake_system()
{
    while (1)
    {
        memcpy(binary_brake_system, &binary_system[5], 2);
        usleep(1000); /* code */
    }

    return 0;
}
