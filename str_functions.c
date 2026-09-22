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

struct str_information** my_strdup(struct str_information** str, int len)
{
    struct str_information** copy = malloc(len * sizeof(struct str_information*));
    
    if (copy == NULL) {
        return NULL; 
    }
    
    for (int i = 0; i <= len; i++) {
        copy[i] = str[i];
    }
    
    return copy;
}

void print_strings (struct str_information** order_array, int number_of_str, const char* restrict name)
{
    FILE* file = fopen(name, "w");
    if (file == NULL)
    {
        perror("Не удалось открыть файл");
        exit(1);
    }

    printf("number_of_str in print_strings: %i", number_of_str);
    for (int i = 0; i < number_of_str; i++)
    {
        my_fputs((char*)((size_t)(order_array[i])), file);
        //fputc('\n', file);
    }

    fclose(file);
}