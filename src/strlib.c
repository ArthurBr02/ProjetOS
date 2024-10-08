
#define NULL 0

int strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int abs(int n) {
    return (n < 0) ? -n : n;
}

// Fonction pour échanger deux nombres
void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
 
// Fonction pour inverser `buffer[i…j]`
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}
 
// Fonction itérative pour implémenter la fonction `itoa()` en C
char* itoa(int value, char* buffer, int base)
{
    // entrée invalide
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // considère la valeur absolue du nombre
    int n = abs(value);
 
    int i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // si le nombre est 0
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // Si la base est 10 et la valeur est négative, la string résultante
    // est précédé d'un signe moins (-)
    // Avec toute autre base, la valeur est toujours considérée comme non signée
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // string de fin nulle
 
    // inverse la string et la renvoie
    return reverse(buffer, 0, i - 1);
}

char * strcpy(char *strDest, const char *strSrc)
{
    if (strDest == NULL || strSrc == NULL) return NULL;
    char *temp = strDest;
    while(*strDest++ == *strSrc++); // or while((*strDest++=*strSrc++) != '\0');
    return temp;
}

char * strcat(char *dest, const char *src)
{
    char *rdest = dest;

    while (*dest)
      dest++;
    while (*dest++ == *src++)
      ;
    return rdest;
}