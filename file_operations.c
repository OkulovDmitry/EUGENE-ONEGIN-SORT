#include "file_operations.h"

void* my_memcpy(void* restrict dest, const void* restrict src, size_t n)
{
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
    int fd = _open(name, _O_RDONLY | _O_BINARY);
   
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

    file_name->file_size = file_info.st_size + sizeof(char);
    file_name->file_buffer = (char* )calloc(file_name->file_size, sizeof(char));
    if (file_name->file_buffer == NULL)
    {
        _close(fd);
        exit(1);
    }

    file_name->bytes_read = _read(fd, file_name->file_buffer, (unsigned int)(file_name->file_size - sizeof(char)));
    if (file_name->bytes_read == -1)
    {
        perror("Ошибка при чтении файлов через _read");
        free(file_name->file_buffer);
        _close(fd);
        exit(1);
    }

    _close(fd);

    file_name->file_buffer[file_name->file_size - 1] = '\0';

}

void break_down_buffer(struct data_and_file_operations* file_name)
{
    for (ssize_t i = 0; i < file_name->bytes_read/sizeof(char); i++)
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

    for (ssize_t i = 0; i < file_name->bytes_read/sizeof(char); i++)
    {
        line_size++;
        if (file_name->file_buffer[i] == '\n' && (i + 2) < file_name->bytes_read/sizeof(char))
        {
            file_name->order_array_of_file[ord_arr_position].order_array = &file_name->file_buffer[i + 2];
            file_name->order_array_of_file[ord_arr_position - 1].size_of_lines = line_size + 1;
            ord_arr_position++;
            line_size = -1;
        }
    }

    file_name->order_array_of_file[ord_arr_position - 1].size_of_lines = line_size;
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

    for (int i = 0; i < number_of_str; i++)
    {
        my_fputs(ptr_array[i]->order_array, file);
    }

    fclose(file);
}