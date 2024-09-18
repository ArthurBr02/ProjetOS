enum Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15
};

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