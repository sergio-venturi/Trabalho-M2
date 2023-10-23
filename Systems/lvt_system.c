// lvt_system.c
#include "../Utils/termios_util.h"
#include <string.h>

char binary_lvtsystem[6] = "00000";
extern char binary_system[13];

int lvt_system()
{
    while (1)
    {
        strncpy(binary_lvtsystem, binary_system, 5);
    }

    return 0;
}
