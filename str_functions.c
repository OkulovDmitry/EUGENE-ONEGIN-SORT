#include "str_functions.h"

char* my_fgets(char* s, int size, FILE* stream)
{
    int i = 0;
    int symbol = '\0';

    while (i < size - 1 && (symbol = fgetc(stream)) != EOF)
    {
        *((char*)((size_t)s+i*sizeof(char))) = (char)symbol;
        i++;
        if (symbol == '\n')
        {
            break;
        }
    }

    if (i == 0){ return NULL; }
    
    *((char*)((size_t)s+(i)*sizeof(char))) = '\0';
    //printf("number of symbols: %i\n", i);
    return s;
}

int my_fputs(const char* str, FILE* stream)
{
    char c;
    int i = 0;
    while((c = *((char*)((size_t)str+i*sizeof(char)))) != '\0')
    {
        i++;
        fputc(c, stream);
    }
    return 0;
}

int my_strcmp (const char* str1, int start_index1, const char* str2, int start_index2, int step)
{
    size_t size1 = 0, size2 = 0;

    //printf("first str: ");
    while (str1[size1] != '\0') {size1++; /*printf("%c", /str1[size1 - 1]);*/}
    //printf("second str: ");
    while (str2[size2] != '\0') {size2++;/* printf("%c", str2[size1 - 1]);*/}

    if (size1 == 0 && size2 == 0) return 0;
    if (size1 == 0) return -1;
    if (size2 == 0) return 1;

    //printf("\nstart_index1 = %i ", start_index1);
    //printf("start-index2 = %i\n", start_index2);

    while (1)
    {
        int stop1 = start_index1 < 0 || start_index1 > size1;
        int stop2 = start_index1 < 0 || start_index2 > size2;

        if (stop1 && stop2) {return 0;}
        if (stop1) {return -1;}
        if (stop2) {return 1;}

        char symbol1 = str1[start_index1];
        char symbol2 = str2[start_index2];

        if ('A' <= str1[start_index1] && str1[start_index1] <= 'Z')
        {
            symbol1 += 'a' - 'A';
        }
        if ('A' <= str2[start_index2] && str2[start_index2] <= 'Z')
        {
            symbol2 += 'a' - 'A';
        }

        if (!('a' <= symbol1 && symbol1 <= 'z') && symbol1 != '\0')
        {
            start_index1 += step;
            continue;
        }
        if (!('a' <= symbol2 && symbol2 <= 'z') && symbol2 != '\0')
        {
            start_index2 += step;
            continue;
        }

        if (symbol1 < symbol2){ return -1; printf("strcmp return -1\n");}
        if (symbol1 > symbol2){ return 1; printf("strcmp return 1\n");}
        start_index1 += step;
        start_index2 += step;
    }
}

char* my_strdup(const char* str)
{
    int len = 0;
    while (str[len++] != '\0') {}
    
    char* copy = malloc(len * sizeof(char));
    
    if (copy == NULL) {
        return NULL; 
    }
    
    for (int i = 0; i <= len; i++) {
        copy[i] = str[i];
    }
    
    return copy;
}