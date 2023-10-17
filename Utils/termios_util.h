// termios_util.h
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void set_termios(struct termios *prev);
void restore_termios(struct termios *prev);
void le_teclado();
