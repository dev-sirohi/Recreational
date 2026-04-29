#ifndef HUFFMAN_ENCODING_DATA_STRUCTURES
#define HUFFMAN_ENCODING_DATA_STRUCTURES

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY_FOR_VECTOR (1 << 12)

typedef struct
{
    size_t size;
    size_t capacity;
    int *arr;
} vector_int;

vector_int *create_vector_int(size_t capacity);
void destroy_vector_int(vector_int *vector);
int vector_int_push_back(vector_int *vector, int value);
int vector_int_remove(vector_int *vector, size_t index);
int vector_int_find_first_index_of(const vector_int *vector, const int value);
int vector_int_find_last_index_of(const vector_int *vector, const int value);

typedef struct
{
    size_t size;
    size_t capacity;
    long long int *arr;
} vector_long;

vector_long *create_vector_long(size_t capacity);
void destroy_vector_long(vector_long *vector);
int vector_long_push_back(vector_long *vector, long value);
int vector_long_remove(vector_long *vector, size_t index);
int vector_long_find_first_index_of(const vector_long *vector, const long value);
int vector_long_find_last_index_of(const vector_long *vector, const long value);

typedef struct
{
    size_t size;
    size_t capacity;
    char *arr;
} vector_char;

vector_char *create_vector_char(size_t capacity);
void destroy_vector_char(vector_char *vector);
int vector_char_push_back(vector_char *vector, char value);
int vector_char_remove(vector_char *vector, size_t index);
int vector_char_find_first_index_of(const vector_char *vector, const char value);
int vector_char_find_last_index_of(const vector_char *vector, const char value);

typedef struct
{
    size_t size;
    size_t capacity;
    char **arr;
} vector_str;

vector_str *create_vector_str(size_t capacity);
void destroy_vector_str(vector_str *vector);
int vector_str_push_back(vector_str *vector, char *value);
int vector_str_remove(vector_str *vector, size_t index);
int vector_str_find_first_index_of(const vector_str *vector, const char *value);
int vector_str_find_last_index_of(const vector_str *vector, const char *value);

/* ERR MACROS */
#define ERR_MEM_ALLOC_UNABLE_TO_ALLOC_VECTOR(vector_name, size)                                    \
    fprintf(stderr,                                                                                \
            "\nErr::Vector::START\n\tFile: %s\n\tLine: %d\n\tMsg: Could not allocate size %zu "    \
            "for vector "                                                                          \
            "%s %s\nErr::END\n",                                                                   \
            __FILE__,                                                                              \
            __LINE__,                                                                              \
            size,                                                                                  \
            vector_name)

#define ERR_VECTOR_INDEX_OUT_OF_BOUNDS(index)                                                      \
    fprintf(stderr,                                                                                \
            "\nErr::Vector::START\n\tFile: %s\n\tLine: %d\n\tMsg: Index %zu out of bounds"         \
            "%s %s\nErr::END\n",                                                                   \
            __FILE__,                                                                              \
            __LINE__,                                                                              \
            index)

#endif
