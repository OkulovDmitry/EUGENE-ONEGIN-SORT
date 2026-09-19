#ifndef MY_QSORT_H
#define MY_QSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void my_qsort(void* arr, uint64_t nmemb, size_t size, int (*compare_ptr)(const void* value1, const void* value2));

#endif //MY_QSORT_H