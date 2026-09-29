# EUGENE-ONEGIN-AI-RAP-GENERATOR

A robust C console application and utility library designed to perform forward and reverse lexicographical alignment and sorting on Alexander Pushkin's novel "Eugene Onegin", as well as generate custom poetic works based on predefined rhyming schemes. The project features a built-in protection system.

> **[RU]** Надёжное консольное приложение и библиотека утилит на C, предназначенные для прямого и обратного лексикографического выравнивания и сортировки текста романа А. С. Пушкина «Евгений Онегин», а также для генерации кастомных стихотворных произведений на основе предопределенных рифмовщиков. Проект включает встроенную систему защиты.

---

## Features / [RU] Возможности
* **Comprehensive Sorting**: Performs forward lexicographical sorting and reverse (rhyming) sorting on text lines, completely ignoring character case and punctuation marks.
* **Algorithmic Poetry**: Generates new poetic works from the source text while strictly preserving the original "Onegin stanza" structure and predefined rhyming schemes.
* **Robust Input Validation**: Clears buffers and handles incorrect formatting gracefully.
* **Safety Assertions**: The built-in protection system safeguards functions against NULL pointers, improper file handling, and runtime errors.
> **[RU]**
> * **Комплексная сортировка**: Выполняет лексикографическую сортировку строк романа в прямом порядке, а также обратную (рифменную) сортировку по концам строк, игнорируя регистр символов и знаки препинания.
> * **Алгоритмическая поэзия**: Генерирует новые стихотворные произведения из исходного текста с сохранением онегинской строфы и заданных схем рифмовки.
> * **Эффективное управление памятью**: Загружает и обрабатывает весь объем текста в рамках единого непрерывного буфера в куче с индексацией через массив указателей.
> * **Защитные утверждения**: Встроенная защита страхует функции от попадания `NULL`-указателей, неправильной обработки файлов и некорректной работы.

---

## Installation & Running / [RU] Сборка и запуск

### Prerequisites / [RU] Требования
Make sure you have `gcc` compiler installed on your system.
> **[RU]** Убедитесь, что в вашей системе установлен компилятор `gcc`.

### Building the Project / [RU] Компиляция
To compile the whole project using `gcc`, run the following command in your terminal:
```bash
gcc .\onegin.c .\my_qsort.c .\file_operations.c .\compares.c .\generator.c 
```
> **[RU]** Чтобы скомпилировать весь проект с помощью `gcc`, выполните команду выше.

### Running / [RU] Запуск
Run the compiled binary without any arguments to start the program:
*Note: Make sure `input.txt` is present in the working directory.*
```bash
./a.exe
```
> **[RU]** Запустите скомпилированный файл без аргументов для запуска программы.
> *Примечание: Убедитесь, что файл `input.txt` находится в рабочей директории.*

---

## Project Structure / [RU] Структура проекта
> * `onegin.c` — Accepts a file containing the text to be processed, invokes the required file sorting functions, and generates an AI-powered novel.
> * `file_operations.h / .c` — Contains functions for file I/O and processing, as well as functions for managing buffers that store file text.
> * `my_qsort.h / .c` — A highly optimized implementation of Quicksort (utilizing Sedgewick's enhanced scheme / Bentley-McIlroy 3-way partitioning) featuring stack overflow protection and degradation prevention on duplicate elements. Written in a generic form (using void* and a comparison function pointer, identical to the standard qsort).
> * `compares.h / .c` — Contains functions for comparing strings in both forward and reverse orders.
> * `generator.h / .c` — Contains functions for identifying valid lines for rhyming and rhymes them according to specified rhyme schemes.

> **[RU]**
> * `onegin.c` — Принимает файл с обрабатываемым текстом и проводит вызов функций сортировки файла нужными и способами и генерации AI романа.
> * `file_operations.h / .c` — Содержит функцци, работающие с файлами(ввод, вывод и обработка файлов), а также функции работы с буферами, содержащими текст файлов.
> * `my_qsort.h / .c` — Высокооптимизированная реализация быстрой сортировки (Улучшенная схема Седжвика / Bentley-McIlroy 3-way partitioning) с защитой от переполнения стека и деградации на дубликатах. Написана в обобщенном виде (через void* и указатель на функцию сравнения, как стандартный qsort).
> * `compares.h / .c` — Содержит функции сравнения строк в прямом и обратном виде.
> * `generator.h / .c` — Содержит функции распознавания валидных для рифмовки строк и рифмует их по заданным схемам рифмовки

