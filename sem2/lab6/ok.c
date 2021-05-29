#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int getInt() {
    int number;
    int result;
    do {
        result = scanf("%d", &number);
        scanf("%*[^\n]s");
        scanf("%*c");
        if (result != 1) {
            printf("Error! Try again\n");
        }
    } while (result != 1);
    return number;
}

char* get_str(FILE *file) {
    char *str = NULL;
    char buf[81];
    size_t size = 0;
    int res;
    do {
        res = fscanf(file, "%80[^\n]", buf);
        if (res == 0) {
            fscanf(file, "%*c"); 
            if (!str) {
                str = malloc(sizeof(char));
                str[0] = '\0';
            }
        } else if (res > 0) {
            size_t len = strlen(buf);
            str = realloc(str, (size+len+1)*sizeof(char));
            memcpy(str+size, buf, len);
            size += len;
            str[size] = '\0';
        }
    } while (res > 0);
    return str;
}

float getFloat() {
    float number;
    int result;
    do {
        result = scanf("%f", &number);
        scanf("%*[^\n]s");
        scanf("%*c");
        if (result != 1) {
            printf("Error! Try again\n");
        }
    } while (result != 1);
    return number;
}


