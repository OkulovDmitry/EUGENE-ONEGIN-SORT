#include "generator.h"

int is_valid_poetic_line(const struct str_information* str)
{
    if (!str || !str->order_array) return 0;

    size_t number_of_letters = 0;

    for (size_t i = 0; str->order_array[i] != '\0'; i++)
    {
        if (ascii[(unsigned char)str->order_array[i]] != 0)
        {
            number_of_letters++;
        }
    }

    return (number_of_letters >= 10);
}

static int check_rhyme(const char* str1, size_t len1, const char* str2, size_t len2)
{
    int index1 = (int)len1 - 2;
    int index2 = (int)len2 - 2;

    int number_of_same_letters = 0;

    while (index1 >= 0 && index2 >= 0 && number_of_same_letters < 3)
    {
        while (index1 >= 0 && ascii[(unsigned char)str1[index1]] == 0) index1--;
        while (index2 >= 0 && ascii[(unsigned char)str2[index2]] == 0) index2--;

        if (index1 < 0 || index2 < 0) break;

        unsigned char c1 = ascii[(unsigned char)str1[index1]];
        unsigned char c2 = ascii[(unsigned char)str2[index2]];

        if (c1 != c2) return 0;

        number_of_same_letters++;
        index1--;
        index2--;
    }

    return (number_of_same_letters >= 2);
}

struct rhyme_data rhyme_search(struct str_information** ptr_reverse, size_t number_of_rhyme)
{
    struct rhyme_data db;
    db.pairs = (struct rhyme_pair*)calloc(number_of_rhyme / 2, sizeof(struct rhyme_pair));
    db.number_of_pairs = 0;

    for (size_t i = 0; i < number_of_rhyme - 1; i++)
    {
        if (check_rhyme((const char*)ptr_reverse[i]->order_array, ptr_reverse[i]->size_of_lines, (const char*)ptr_reverse[i + 1]->order_array, ptr_reverse[i + 1]->size_of_lines))
        {
            db.pairs[db.number_of_pairs].line1 = (const char*)ptr_reverse[i]->order_array;
            db.pairs[db.number_of_pairs].line2 = (const char*)ptr_reverse[i + 1]->order_array;
            db.number_of_pairs++;
            
            i++;
        }
    }

    return db;
}

void generate_quadratian(const struct rhyme_data* db, const char* scheme)
{
    if (db->number_of_pairs < 2) {
        printf("Недостаточно рифм для генерации!\n");
        return;
    }

    size_t index1 = rand() % db->number_of_pairs;
    size_t index2 = rand() % db->number_of_pairs;
    while (index2 == index1) index2 = rand() % db->number_of_pairs;

    struct rhyme_pair pair1 = db->pairs[index1];
    struct rhyme_pair pair2 = db->pairs[index2];

    printf("\n=== ONEGIN AI RAP (%s) ===\n\n", scheme);

    if (strcmp(scheme, "ABAB") == 0) {
        printf("%s\n%s\n%s\n%s\n", pair1.line1, pair2.line1, pair1.line2, pair2.line2);
    } 
    else if (strcmp(scheme, "AABB") == 0) {
        printf("%s\n%s\n%s\n%s\n", pair1.line1, pair1.line2, pair2.line1, pair2.line2);
    } 
    else if (strcmp(scheme, "ABBA") == 0) {
        printf("%s\n%s\n%s\n%s\n", pair1.line1, pair2.line1, pair2.line2, pair1.line2);
    }
}