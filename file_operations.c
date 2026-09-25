#include "file_operations.h"

void* my_memcpy(void* restrict dest, const void* restrict src, size_t n)
{
    // Проверка на NULL (если n > 0)
    if (dest == NULL || src == NULL) {
        return dest;
    }

    unsigned char* restrict d = (unsigned char* restrict)dest;
    const unsigned char* restrict s = (const unsigned char* restrict)src;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }

    return dest;
}

void read_from_file(const char* restrict name, struct data_and_file_operations* file_name)
{
    int fd = _open(name, _O_RDONLY | _O_BINARY); //сука ебучая запятая вместо побитового или не давала открыть файл в нормальном бинарном режиме и ебала мне мозги тем что bytes_read != file_size
    
    if (fd == -1) {
        perror("Не удалось открыть файл");
        exit(1);
    }
    struct _stat file_info;
    if (_fstat(fd, &file_info) != 0)
    {
        perror("Ошибка при вызове _fstat");
        _close(fd);
        exit(1);
    }

    file_name->file_size = file_info.st_size + 1*sizeof(char);
    file_name->file_buffer = (char* )calloc(file_name->file_size, sizeof(char));
    if (file_name->file_buffer == NULL)
    {
        _close(fd);
        exit(1);
    }

    file_name->bytes_read = _read(fd, file_name->file_buffer, (unsigned int)(file_name->file_size - 1*sizeof(char)));
    if (file_name->bytes_read == -1)
    {
        perror("Ошибка при чтении файлов через _read");
        free(file_name->file_buffer);
        _close(fd);
        exit(1);
    }

    //printf("file_size: %llu\n", file_name->file_size);
    //printf("bytes read: %i\n", file_name->bytes_read);

    _close(fd);

    file_name->file_buffer[file_name->file_size - 1] = '\0';

    /*for (int i = 0 ; i < file_name->file_size; i++)
    {
        printf("%c", file_name->file_buffer[i]);
    }*/
}

void break_down_buffer(struct data_and_file_operations* file_name)
{
    /*for (int i = 0 ; i < file_name->file_size; i++)
    {
        printf("%c", file_name->file_buffer[i]);
    }*/

    for (int i = 0; i < file_name->bytes_read/sizeof(char); i++)
    {
        if (file_name->file_buffer[i] == '\r')
        {
            file_name->file_buffer[i] = '\n';
        }
        else if (file_name->file_buffer[i] == '\n')
        {
            file_name->file_buffer[i] = '\0';
            file_name->number_of_str++;
        }
    }

    file_name->order_array_of_file = (struct str_information*)calloc(file_name->number_of_str, sizeof(struct str_information));
    
    file_name->order_array_of_file[0].order_array = file_name->file_buffer;
    int ord_arr_position = 1;
    size_t line_size = 0;

    for (int i = 0; i < file_name->bytes_read/sizeof(char); i++)
    {
        line_size++;
        if (file_name->file_buffer[i] == '\n' && (i + 2) < file_name->bytes_read/sizeof(char))
        {
            file_name->order_array_of_file[ord_arr_position].order_array = &file_name->file_buffer[i + 2];
            file_name->order_array_of_file[ord_arr_position - 1].size_of_lines = line_size + 1;
            //printf("%llu\n", file_name->order_array_of_file[ord_arr_position - 1].size_of_lines);
            ord_arr_position++;
            line_size = -1;
        }
    }

    file_name->order_array_of_file[ord_arr_position - 1].size_of_lines = line_size;
    //printf("%llu\n", file_name->order_array_of_file[ord_arr_position - 1].size_of_lines);

    //printf("last line: %s\n", file_name->order_array_of_file[12].order_array);
    //printf("number of str: %i\n", file_name->number_of_str);
    //printf("%i line before sort: %s\n", 1, file_name->order_array[0]);
    //for (int i = 0; i < file_name->number_of_str; i++)
    //{
    //    printf("%i line: %s", i + 1, file_name->order_array_of_file[i].order_array);
    //}
}

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

void print_strings (struct str_information** ptr_array, int number_of_str, const char* restrict name)
{
    FILE* file = fopen(name, "w");
    if (file == NULL)
    {
        perror("Не удалось открыть файл");
        exit(1);
    }

    //printf("number_of_str in print_strings: %i\n", number_of_str);
    for (int i = 0; i < number_of_str; i++)
    {
        my_fputs(ptr_array[i]->order_array, file);
        //printf("I put '%s' in file\n", order_array_of_file->order_array_of_file[i].order_array);
    }

    fclose(file);
}