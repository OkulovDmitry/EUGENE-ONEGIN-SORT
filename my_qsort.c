#include "my_qsort.h"

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