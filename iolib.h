#ifndef INCLUDE_IOLIB_H
#define INCLUDE_IOLIB_H

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void write(char *buf, unsigned int len);
void clear();
int findLineNb(int);

#endif /* INCLUDE_IOLIB_H */