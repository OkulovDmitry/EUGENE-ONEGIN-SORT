#ifndef MY_QSORT_H
#define MY_QSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void my_qsort(void* arr, uint64_t nmemb, size_t size, int (*compare_ptr)(const void* value1, const void* value2));
void insertion_sort(void* arr, uint64_t nmemb, size_t size, int (*compare_ptr)(const void* value1, const void* value2));
void swap_elements(void* arr, int64_t index1, int64_t index2, size_t size);
uint64_t binsearch(void* arr, unsigned char* elem, size_t size, uint64_t left, uint64_t right, int (*compare_ptr)(const void* value1, const void* value2));

#endif //MY_QSORT_H