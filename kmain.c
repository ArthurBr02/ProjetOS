#define FB_BLACK     0
#define FB_BLUE      1
#define FB_GREEN     2
#define FB_CYAN      3
#define FB_RED       4
#define FB_MAGENTA   5
#define FB_BROWN     6
#define FB_LIGHT_GREY 7
#define FB_DARK_GREY 8
#define FB_LIGHT_BLUE 9
#define FB_LIGHT_GREEN 10
#define FB_LIGHT_CYAN 11
#define FB_LIGHT_RED 12
#define FB_LIGHT_MAGENTA 13
#define FB_LIGHT_BROWN 14
#define FB_WHITE 15

#define MAX_ROW_LENGTH 158
#define CHAR_SIZE 2

#define TAB_SIZE 255


void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
int strlen(const char *str);

int kmain() {
    char c = 'H';
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
    }
    return 0;
}

char *fb = (char *) 0x000B8000;

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

int strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}