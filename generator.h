#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "file_operations.h"
#include "compares.h"

struct rhyme_pair
{
    const char* line1;
    const char* line2;
};

struct rhyme_data
{
    struct rhyme_pair* pairs;
    size_t number_of_pairs;
};

struct rhyme_data rhyme_search(struct str_information** ptr_reverse, size_t number_of_str);
void generate_quadratian(const struct rhyme_data* dtb, const char* scheme);
int is_valid_poetic_line(const struct str_information* str);
static int check_rhyme(const char* str1, size_t len1, const char* str2, size_t len2);

#endif