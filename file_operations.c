#include "file_operations.h"

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
            file_name->number_of_str++;
        }
        else if (file_name->file_buffer[i] == '\n')
        {
            file_name->file_buffer[i] = '\0';
        }
    }

    file_name->order_array_of_file = (struct str_information*)calloc(file_name->number_of_str, sizeof(char*) + sizeof(size_t));
    
    file_name->order_array_of_file[0].order_array = file_name->file_buffer;
    int ord_arr_position = 1;

    for (int i = 0; i < file_name->bytes_read/sizeof(char); i++)
    {
        if (file_name->file_buffer[i] == '\n' && (i + 2) < file_name->bytes_read/sizeof(char))
        {
            file_name->order_array_of_file[ord_arr_position++].order_array = &file_name->file_buffer[i + 2];
            file_name->order_array_of_file[ord_arr_position - 1].size_of_lines = (size_t)(file_name->order_array_of_file[ord_arr_position].order_array - file_name->order_array_of_file[ord_arr_position - 1].order_array);
        }
    }

    //printf("last line: %s", file_name->order_array[number_of_str - 1]);
    //printf("number of str: %i\n", file_name->number_of_str);
    //printf("%i line before sort: %s\n", 1, file_name->order_array[0]);
    /*for (int i = 0; i < file_name->number_of_str; i++)
    {
        printf("%i line: %s", i + 1, file_name->order_array[i]);
    }*/
}