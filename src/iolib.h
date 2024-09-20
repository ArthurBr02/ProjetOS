#ifndef INCLUDE_IOLIB_H
#define INCLUDE_IOLIB_H

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

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void write(char *buf, unsigned int len);
void writec(char *buf, unsigned int len, unsigned char fg, unsigned char bg);
void clear();
int findLineNb(int);
void log(char *buf, unsigned int len, char *severness);

#endif /* INCLUDE_IOLIB_H */