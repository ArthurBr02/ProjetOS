/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

#define MAX_ROW_LENGTH 158
#define CHAR_SIZE 2
#define VALUE_FIRST_CHAR_CURSOR 80

#include "iolib.h"
#include "io.h"
#include "serial.h"
#include "strlib.h"

char *fb = (char *) 0x000B8000;
unsigned int state = 0;


/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}



/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

/*
Write a char buffer to the framebuffer
 */
void write(char *buf, unsigned int len) {
    // Nombre de caractères sur la ligne actuelle
    unsigned int nbCharLine = 0;
	for(unsigned int i=0;i<len;i++){
        char c = *buf++;
        if (c == '\n') {
            state += MAX_ROW_LENGTH - (state % MAX_ROW_LENGTH);
            state += 2 * findLineNb(state);
            nbCharLine = 0;
            continue;
        }
		fb_write_cell(state,c, BLACK, WHITE);
		state+=2;
        nbCharLine++;
	}
	fb_move_cursor(VALUE_FIRST_CHAR_CURSOR * findLineNb(state) + nbCharLine);
}

/*
Write a char buffer to the framebuffer with colors specified
 */
void writec(char *buf, unsigned int len, unsigned char fg, unsigned char bg) {
    // Nombre de caractères sur la ligne actuelle
    unsigned int nbCharLine = 0;
	for(unsigned int i=0;i<len;i++){
        char c = *buf++;
        if (c == '\n') {
            state += MAX_ROW_LENGTH - (state % MAX_ROW_LENGTH);
            state += 2 * findLineNb(state);
            nbCharLine = 0;
            continue;
        }
		fb_write_cell(state,c, fg, bg);
		state+=2;
        nbCharLine++;
	}
	fb_move_cursor(VALUE_FIRST_CHAR_CURSOR * findLineNb(state) + nbCharLine);
}

/*
Clear the framebuffer
 */
void clear() {
    for (int i = 0; i < MAX_ROW_LENGTH * 25; i++) {
        fb_write_cell(i * CHAR_SIZE, ' ', BLACK, WHITE);
    }
    fb_move_cursor(0);
    state = 0;
}

/*
Return the current line number on the frame buffer
*/
int findLineNb(int state) {
    return state / MAX_ROW_LENGTH;
}

void log(char *buf, unsigned int len, char *severness) {
    char buf2[strlen(severness) + len + 1];
    strcpy(buf2, severness);
    strcat(buf2, buf);
    write(buf2, strlen(buf2));
}