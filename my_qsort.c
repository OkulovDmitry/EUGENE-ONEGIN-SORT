#include "my_qsort.h"

uint64_t binsearch(void* arr, unsigned char* elem, size_t size, uint64_t left, uint64_t right, int (*compare_ptr)(const void* value1, const void* value2))
{
    while (left < right)
    {
        uint64_t mid = (right + left) / 2;
        int res = compare_ptr((void*)((size_t)arr + mid*size), elem);
        if (res > 0) {right = mid;}
        else {left = mid + 1;}
    }
    return left;
}

void insertion_sort(void* arr, uint64_t nmemb, size_t size, int (*compare_ptr)(const void* value1, const void* value2))
{
    for (uint64_t i = 1; i < nmemb; i++)
    {
        unsigned char elem[size];
        for (size_t p = 0; p < size; p++)
        {
            elem[p] = *((unsigned char* restrict)((size_t)(arr) + i * size + p));
        }
        uint64_t k = binsearch(arr, elem, size, 0, i, compare_ptr);

        unsigned char a = '\0';
        for (uint64_t m = i; m > k; m--)
        {
            for (size_t n = 0; n < size; n++)
            {
                *((unsigned char*)arr + m * size + n) = *((unsigned char*)arr + (m - 1) * size + n);
            }
        }

        for (size_t p = 0; p < size; p++)
        {
            *((unsigned char*)arr + k * size + p) = elem[p];
        }
    }
}

void swap_elements(void* arr, int64_t index1, int64_t index2, size_t size)
{
    if (index1 == index2) return;
    unsigned char* p1 = (unsigned char*)arr + index1 * size;
    unsigned char* p2 = (unsigned char*)arr + index2 * size;
    for (size_t i = 0; i < size; i++)
    {
        unsigned char a = p1[i];
        p1[i] = p2[i];
        p2[i] = a;
    }
}

void my_qsort(void* arr, uint64_t nmemb, size_t size, int (*compare_ptr)(const void* value1, const void* value2))
{
    while (nmemb > 1)
    {
        if (nmemb < 16)
        {
            insertion_sort(arr, nmemb, size, compare_ptr);
            break;
        }
        int64_t left = -1;
        int64_t right = nmemb;
        int64_t p = -1;
        int64_t q = nmemb;
        unsigned char pivot[size];

        int64_t pivot_index = rand() % (nmemb - 1);
        
        for (int i = 0; i < size; i++)
        {
            pivot[i] = *((unsigned char* restrict)((size_t)(arr) + size*(pivot_index) + i));
        }

        while (1)
        {
            int cmp_left = 0;
            int cmp_right = 0;
            do
            {
                left++;
                cmp_left = compare_ptr((void*)((size_t)arr + size*left), pivot);
            } while (cmp_left < 0);

            do
            {
                right--;
                cmp_right = compare_ptr((void*)((size_t)arr + size*right), pivot);
            } while (cmp_right > 0);

            if (left >= right)
            {
                break;
            }
            
            swap_elements(arr, left, right, size);

            if (cmp_right == 0)
            {
                p++;
                swap_elements(arr, p, left, size);
            }
            if (cmp_left == 0)
            {
                q--;
                swap_elements(arr, q, right, size);
            }
        }

        int64_t i = left;
        int64_t j = left - 1;

        for (int k = 0; k <= p; k++, j--)
        {
            swap_elements(arr, k, j, size);
        }
        for (int k = nmemb - 1; k >= q; k--, i++)
        {
            swap_elements(arr, k, i, size);
        }

        int64_t left_size = j + 1;
        int64_t right_size = nmemb - i;

        if (left_size < right_size)
        {
            my_qsort(arr, left_size, size, compare_ptr);
            arr = (char*)arr + i * size;
            nmemb = right_size;
        }
        else
        {
            my_qsort((char*)arr + i * size, right_size, size, compare_ptr);
            nmemb = left_size;
        }
    }
}