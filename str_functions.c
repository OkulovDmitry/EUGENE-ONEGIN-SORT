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

int my_strcmp (const char *str1, const char *str2)
{
    int i = 0;
    int j = 0;
    while (str1[i] != '\0' || str2[j] != '\0')
    {
        char symbol1 = str1[i];
        char symbol2 = str2[j];

        if ('A' <= str1[i] && str1[i] <= 'Z')
        {
            symbol1 += 'a' - 'A';
        }
        if ('A' <= str2[j] && str2[j] <= 'Z')
        {
            symbol2 += 'a' - 'A';
        }

        if (!('a' <= symbol1 && symbol1 <= 'z') && symbol1 != '\0')
        {
            i++;
            continue;
        }
        if (!('a' <= symbol2 && symbol2 <= 'z') && symbol2 != '\0')
        {
            j++;
            continue;
        }

        if (symbol1 < symbol2){ return -1;}
        if (symbol1 > symbol2){ return 1;}
        if (symbol1 == '\0' && symbol2 == '\0'){ return 0;}
        i++;
        j++;
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