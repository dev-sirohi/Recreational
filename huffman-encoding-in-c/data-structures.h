#ifndef HUFFMAN_ENCODING_DATA_STRUCTURES
#define HUFFMAN_ENCODING_DATA_STRUCTURES

#include <mem.h>
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

typedef struct
{
    size_t size;
    size_t capacity;
    long long int *arr;
} vector_long;

typedef struct
{
    size_t size;
    size_t capacity;
    char *arr;
} vector_char;

typedef struct
{
    size_t size;
    size_t capacity;
    char **arr;
} vector_str;

vector_int *create_vector_int(size_t capacity)
{
    if (capacity == 0)
    {
        capacity = 1;
    }
    vector_int *vector = (vector_int *)malloc(sizeof(vector_int));
    if (vector == NULL)
    {
        return NULL;
    }

    vector->size     = 0;
    vector->capacity = capacity;
    vector->arr      = (int *)calloc(capacity, sizeof(int));
    if (vector->arr == NULL)
    {
        free(vector);
        return NULL;
    }

    return vector;
}

void destroy_vector_int(vector_int *vector)
{
    if (vector == NULL)
    {
        return;
    }

    free(vector->arr);
    free(vector);

    return;
}

static int resize_vector_int(vector_int *vector, int decrease_flag)
{
    size_t new_capacity = 0;
    size_t current_size = vector->size;

    if (decrease_flag == 1)
    {
        new_capacity = vector->capacity / 2;
    }
    else
    {
        new_capacity = vector->capacity * 2;
    }

    if (new_capacity * sizeof(int) > MAX_MEMORY_FOR_VECTOR)
    {
        printf("%s", "resize_vector_int :: Memory out of bounds");
        return 1;
    }
    if (new_capacity == 0)
    {
        printf("%s", "resize_vector_int :: Cannot resize to size 0");
    }

    int *temp = (int *)realloc(vector->arr, new_capacity * sizeof(int));
    if (temp == NULL)
    {
        return 1;
    }

    vector->arr = temp;

    for (size_t i = current_size; i < new_capacity; i++)
    {
        vector->arr[i] = 0;
    }

    vector->capacity = new_capacity;

    return 0;
}

int push_int(vector_int *vector, int value)
{
    if (vector->size == vector->capacity)
    {
        if (resize_vector_int(vector, 0))
        {
            return 1;
        }
    }

    vector->arr[vector->size] = value;
    vector->size++;
    return 0;
}

int remove_int(vector_int *vector, size_t index)
{
    if (vector->size <= index)
    {
        printf("remove_int :: Index out of bounds");
        return 0;
    }

    int removed_value = vector->arr[index];
    for (size_t i = index + 1; i < vector->size; i++)
    {
        vector->arr[i - 1] = vector->arr[i];
    }
    vector->size--;

    if (vector->size <= (vector->capacity / 2))
    {
        resize_vector_int(vector, 1);
    }

    return removed_value;
}

#endif
