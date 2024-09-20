#define MAX_ROW_LENGTH 158
#define CHAR_SIZE 2

#define TAB_SIZE 255

#include "iolib.h"
#include "strlib.h"
#include "serial.h"


void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
int strlen(const char *str);

int kmain() {
    clear();
    /*char c = 'H';
    fb_write_cell(0, c, FB_BLACK, FB_RED);

    char chartab[TAB_SIZE] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A'};
    for (int i = 0; i < 11; i++) {
        fb_write_cell(i * CHAR_SIZE, chartab[i], FB_BLACK, FB_RED);
    }

    char chartab2[TAB_SIZE] = "Hello, World!";
    int len = strlen(chartab2);
    for (int i = 0; i < len; i++) {
        char ch = chartab2[i];
        fb_write_cell(i * CHAR_SIZE + MAX_ROW_LENGTH + 2, ch, FB_BLACK, FB_RED);
    }*/

    // Test move cursor
    //fb_move_cursor(85);

    char buf[] = "Hello, World!\ntest nouvelle ligne\nnouvelle ligne 2";
    char buf2[] = "\nHello, World!\ntest nouvelle ligne\nnouvelle ligne 2\n";
    write(buf, strlen(buf));
    write(buf2, strlen(buf2));
    
    
    int i = 256410;
    //int size;
    //if (i >= 0) size = i/10 + 1;
    //else size = (-1 * i)/10 + 1;

    char bufi[33];

    int base = 10;

    itoa(i, bufi, base);
    writec(bufi, strlen(bufi), RED, LIGHT_MAGENTA);

    serial_configure_baud_rate(1, 1);
    serial_configure_line(1);
    serial_configure_buffers(1);
    serial_configure_modem(1);
    serial_write(buf, strlen(buf));

    //log(buf, strlen(buf), "INFO: ");

    return 0;
}