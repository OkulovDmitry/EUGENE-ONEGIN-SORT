#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

const int MAX_STR = 100;
const int MAX_NUMBER_OF_STR = 100;

int read_from_file(const char* restrict name, char text[][MAX_STR]);
char* fgets(char* s, int size, FILE* stream);

void print_strings (char data[][MAX_STR], int number_of_str, const char* restrict name);
int my_fputs(const char str[], FILE* stream);

int strings_compare(const void* value1, const void* value2);
int my_strcmp (const char* str1, const char* str2);

void my_qsort(void* arr, uint64_t nmemb, size_t size, int (*compare_ptr)(const void* value1, const void* value2));



int main()
{
    char text[MAX_NUMBER_OF_STR][MAX_STR] = {};
    int number_of_str = read_from_file("input.txt", text);
    //printf("number of str: %i\n", number_of_str);
    //printf("%i line before sort: %s\n", 1, text[0]);

    my_qsort(text, number_of_str, MAX_STR*sizeof(char), strings_compare);
    print_strings(text, number_of_str, "output.txt");
    //printf("%i line after sort: %s\n", 2, text[1]);
    
    return 0;
}

int read_from_file(const char* restrict name, char text[][MAX_STR])
{
    FILE* file = fopen(name, "r");
    int number_of_lines = 0;
    while (fgets(text[number_of_lines++], MAX_STR, file) != NULL) {}
        //printf("%i line: %s\n", number_of_lines-1, text[number_of_lines-1]);
    fclose(file);
    return number_of_lines - 1;
}

char* fgets(char* s, int size, FILE* stream)
{
    int i = 0;
    while (i < size && (*((int*)((size_t)s+i*sizeof(char))) = fgetc(stream)) != EOF)
    {
        if (*((char*)((size_t)s+i*sizeof(char))) == '\n')
        {
            *((char*)((size_t)s+i*sizeof(char))) = '\0';
            break;
        }
        i++;
    }
    if (*((int*)((size_t)s+i*sizeof(char))) == EOF)
    {
        *((char*)((size_t)s+i*sizeof(char))) = '\0';
        return NULL;
    }
    //printf("number of symbols: %i\n", i);
    return s;
}

void print_strings (char data[][MAX_STR], int number_of_str, const char* restrict name)
{ 
    FILE* file = fopen(name, "w");
    for (int i = 0; i < number_of_str; i++)
    {
        my_fputs(data[i], file);
    }
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
    fputc('\n', stream);
    return 0;
}

int strings_compare(const void* value1, const void* value2)
{
    char* value1_res = (char*)value1;
    char* value2_res = (char*)value2;

    return strcmp(value1_res, value2_res);
}

int my_strcmp (const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] != '\0' || str2[i] != '\0')
    {
        if (str1[i] < str2[i]){ return -1;}
        if (str1[i] > str2[i++]){ return 1;}
        if (str1[i] == '\0' && str2[i] == '\0'){ return 0;}
    }
}

void my_qsort(void* arr, uint64_t nmemb, size_t size, int (*compare_ptr)(const void* value1, const void* value2))
{
    if (nmemb > 1)
    {
        int64_t i = -1;
        int64_t j = (int64_t)nmemb;
        unsigned char pivot[size];

        int64_t rand_pivot = (nmemb-1)/2;
        
        for (int i = 0; i < size; i++)
        {
            pivot[i] = *((unsigned char* restrict)((size_t)(arr) + size*(rand_pivot) + i));
        }

        while (i < j)
        {
            do
            {
                i++;
            } while (compare_ptr((void*)((size_t)arr + size*i), pivot) == -1);

            do
            {
                j--;
            } while (compare_ptr((void*)((size_t)arr + size*j), pivot) == 1);

            if (i >= j)
            {
                break;
            }
            
            unsigned char a = '\0';

            for (int k = 0; k < size; k++)
            {
                a = *((unsigned char* restrict)((size_t)arr + size*i + k));
                *((unsigned char* restrict)((size_t)arr + size*i + k)) = *((unsigned char* restrict)((size_t)arr + size*j + k));
                *((unsigned char* restrict)((size_t)arr + size*j + k)) = a;
            }
        }

        void* right_arr = (void*)((size_t)arr + size*(j+1));
        my_qsort(arr,             j+1, size, compare_ptr);
        my_qsort(right_arr, nmemb-j-1, size, compare_ptr);
    }
}