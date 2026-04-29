#include "cvectors.h"
#include "exceptions.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* VECTOR_INT:START */

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
    if (vector != NULL)
    {
        if (vector->arr != NULL)
        {
            free(vector->arr);
        }
        free(vector);
    }

    return;
}

static void resize_vector_int(vector_int *vector, int decrease_flag)
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
        RETERR;
    }
    if (new_capacity == 0)
    {
        printf("%s", "resize_vector_int :: Cannot resize to size 0");
        RETERR;
    }

    int *temp = (int *)realloc(vector->arr, new_capacity * sizeof(int));
    if (temp == NULL)
    {
        RETERR;
    }

    vector->arr = temp;

    for (size_t i = current_size; i < new_capacity; i++)
    {
        vector->arr[i] = 0;
    }

    vector->capacity = new_capacity;
}

int vector_int_push_back(vector_int *vector, int value)
{
    if (vector->size == vector->capacity)
    {
        resize_vector_int(vector, 0);
    }

    vector->arr[vector->size] = value;
    vector->size++;
    return OK;
}

int vector_int_remove(vector_int *vector, size_t index)
{
    if (vector == NULL)
    {
        RETERR;
    }

    if (vector->size <= index)
    {
        ERR_VECTOR_INDEX_OUT_OF_BOUNDS(index);
        RETERR;
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

int vector_int_find_first_index_of(const vector_int *vector, const int value)
{
    if (vector == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < vector->size; i++)
    {
        if (vector->arr[i] == value)
        {
            return i;
        }
    }

    return -1;
}

int vector_int_find_last_index_of(const vector_int *vector, const int value)
{
    if (vector == NULL)
    {
        return -1;
    }

    if (vector->size == 0)
    {
        return -1;
    }

    for (size_t i = vector->size - 1; i >= 0; i--)
    {
        if (vector->arr[i] == value)
        {
            return i;
        }
    }

    return -1;
}

void vector_int_reverse(vector_int *vector)
{
    if (vector == NULL)
    {
        return;
    }

    int left_ptr  = 0;
    int right_ptr = vector->size - 1;

    while (left_ptr < right_ptr)
    {
        int temp               = vector->arr[left_ptr];
        vector->arr[left_ptr]  = vector->arr[right_ptr];
        vector->arr[right_ptr] = temp;

        left_ptr++;
        right_ptr--;
    }
}

/* VECTOR_INT:END */

/* VECTOR_LONG:START */

vector_long *create_vector_long(size_t capacity)
{
    if (capacity == 0)
    {
        capacity = 1;
    }
    vector_long *vector = (vector_long *)malloc(sizeof(vector_long));
    if (vector == NULL)
    {
        return NULL;
    }

    vector->size     = 0;
    vector->capacity = capacity;
    vector->arr      = (long long *)calloc(capacity, sizeof(long long));
    if (vector->arr == NULL)
    {
        free(vector);
        return NULL;
    }

    return vector;
}

void destroy_vector_long(vector_long *vector)
{
    if (vector != NULL)
    {
        if (vector->arr != NULL)
        {
            free(vector->arr);
        }
        free(vector);
    }

    return;
}

static void resize_vector_long(vector_long *vector, int decrease_flag)
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

    if (new_capacity * sizeof(long long) > MAX_MEMORY_FOR_VECTOR)
    {
        printf("%s", "resize_vector_long :: Memory out of bounds");
        RETERR;
    }
    if (new_capacity == 0)
    {
        printf("%s", "resize_vector_long :: Cannot resize to size 0");
        RETERR;
    }

    long long *temp = (long long *)realloc(vector->arr, new_capacity * sizeof(long long));
    if (temp == NULL)
    {
        RETERR;
    }

    vector->arr = temp;

    for (size_t i = current_size; i < new_capacity; i++)
    {
        vector->arr[i] = 0;
    }

    vector->capacity = new_capacity;
}

long long vector_long_push_back(vector_long *vector, long long value)
{
    if (vector->size == vector->capacity)
    {
        resize_vector_long(vector, 0);
    }

    vector->arr[vector->size] = value;
    vector->size++;
    return OK;
}

long long vector_long_remove(vector_long *vector, size_t index)
{
    if (vector == NULL)
    {
        RETERR;
    }

    if (vector->size <= index)
    {
        ERR_VECTOR_INDEX_OUT_OF_BOUNDS(index);
        RETERR;
    }

    long long removed_value = vector->arr[index];
    for (size_t i = index + 1; i < vector->size; i++)
    {
        vector->arr[i - 1] = vector->arr[i];
    }
    vector->size--;

    if (vector->size <= (vector->capacity / 2))
    {
        resize_vector_long(vector, 1);
    }

    return removed_value;
}

int vector_long_find_first_index_of(const vector_long *vector, const long long value)
{
    if (vector == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < vector->size; i++)
    {
        if (vector->arr[i] == value)
        {
            return i;
        }
    }

    return -1;
}

int vector_long_find_last_index_of(const vector_long *vector, const long long value)
{
    if (vector == NULL)
    {
        return -1;
    }

    if (vector->size == 0)
    {
        return -1;
    }

    for (size_t i = vector->size - 1; i >= 0; i--)
    {
        if (vector->arr[i] == value)
        {
            return i;
        }
    }

    return -1;
}

void vector_long_reverse(vector_long *vector)
{
    if (vector == NULL)
    {
        return;
    }

    long long left_ptr  = 0;
    long long right_ptr = vector->size - 1;

    while (left_ptr < right_ptr)
    {
        long long temp         = vector->arr[left_ptr];
        vector->arr[left_ptr]  = vector->arr[right_ptr];
        vector->arr[right_ptr] = temp;

        left_ptr++;
        right_ptr--;
    }
}

/* VECTOR_LONG:END */

/* VECTOR_CHAR:START */

vector_char *create_vector_char(size_t capacity)
{
    if (capacity == 0)
    {
        capacity = 1;
    }
    vector_char *vector = (vector_char *)malloc(sizeof(vector_char));
    if (vector == NULL)
    {
        return NULL;
    }

    vector->size     = 0;
    vector->capacity = capacity;
    vector->arr      = (char *)calloc(capacity, sizeof(char));
    if (vector->arr == NULL)
    {
        free(vector);
        return NULL;
    }

    return vector;
}

void destroy_vector_char(vector_char *vector)
{
    if (vector != NULL)
    {
        if (vector->arr != NULL)
        {
            free(vector->arr);
        }
        free(vector);
    }

    return;
}

static void resize_vector_char(vector_char *vector, int decrease_flag)
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

    if (new_capacity * sizeof(char) > MAX_MEMORY_FOR_VECTOR)
    {
        printf("%s", "resize_vector_char :: Memory out of bounds");
        RETERR;
    }
    if (new_capacity == 0)
    {
        printf("%s", "resize_vector_char :: Cannot resize to size 0");
        RETERR;
    }

    char *temp = (char *)realloc(vector->arr, new_capacity * sizeof(char));
    if (temp == NULL)
    {
        RETERR;
    }

    vector->arr = temp;

    for (size_t i = current_size; i < new_capacity; i++)
    {
        vector->arr[i] = 0;
    }

    vector->capacity = new_capacity;
}

int vector_char_push_back(vector_char *vector, char value)
{
    if (vector->size == vector->capacity)
    {
        resize_vector_char(vector, 0);
    }

    vector->arr[vector->size] = value;
    vector->size++;
    return OK;
}

char vector_char_remove(vector_char *vector, size_t index)
{
    if (vector == NULL)
    {
        RETERR;
    }

    if (vector->size <= index)
    {
        ERR_VECTOR_INDEX_OUT_OF_BOUNDS(index);
        RETERR;
    }

    char removed_value = vector->arr[index];
    for (size_t i = index + 1; i < vector->size; i++)
    {
        vector->arr[i - 1] = vector->arr[i];
    }
    vector->size--;

    if (vector->size <= (vector->capacity / 2))
    {
        resize_vector_char(vector, 1);
    }

    return removed_value;
}

int vector_char_find_first_index_of(const vector_char *vector, const char value)
{
    if (vector == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < vector->size; i++)
    {
        if (vector->arr[i] == value)
        {
            return i;
        }
    }

    return -1;
}

int vector_char_find_last_index_of(const vector_char *vector, const char value)
{
    if (vector == NULL)
    {
        return -1;
    }

    if (vector->size == 0)
    {
        return -1;
    }

    for (size_t i = vector->size - 1; i >= 0; i--)
    {
        if (vector->arr[i] == value)
        {
            return i;
        }
    }

    return -1;
}

/* VECTOR_CHAR:END */

/* VECTOR_STR:START */

vector_str *create_vector_str(size_t capacity)
{
    if (capacity == 0)
    {
        capacity = 1;
    }
    vector_str *vector = (vector_str *)malloc(sizeof(vector_str));
    if (vector == NULL)
    {
        return NULL;
    }

    vector->size     = 0;
    vector->capacity = capacity;
    vector->arr      = (char **)calloc(capacity, sizeof(char *));
    if (vector->arr == NULL)
    {
        free(vector);
        return NULL;
    }

    return vector;
}

void destroy_vector_str(vector_str *vector)
{
    if (vector != NULL)
    {
        if (vector->arr != NULL)
        {
            for (size_t i = 0; i < vector->size; i++)
            {
                if (vector->arr[i] == NULL)
                {
                    continue;
                }
                free(vector->arr[i]);
            }
            free(vector->arr);
        }
        free(vector);
    }

    return;
}

static void resize_vector_str(vector_str *vector, int decrease_flag)
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

    if (new_capacity * sizeof(char *) > MAX_MEMORY_FOR_VECTOR)
    {
        printf("%s", "resize_vector_str :: Memory out of bounds");
        RETERR;
    }
    if (new_capacity == 0)
    {
        printf("%s", "resize_vector_str :: Cannot resize to size 0");
        RETERR;
    }

    char **temp = (char **)realloc(vector->arr, new_capacity * sizeof(char *));
    if (temp == NULL)
    {
        RETERR;
    }

    vector->arr = temp;

    for (size_t i = current_size; i < new_capacity; i++)
    {
        vector->arr[i] = NULL;
    }

    vector->capacity = new_capacity;
}

int vector_str_push_back(vector_str *vector, char *value)
{
    if (vector->size == vector->capacity)
    {
        resize_vector_str(vector, 0);
    }

    vector->arr[vector->size] = strdup(value);
    vector->size++;
    return OK;
}

char *vector_str_remove(vector_str *vector, size_t index)
{
    if (vector == NULL)
    {
        RETERR;
    }

    if (vector->size <= index)
    {
        ERR_VECTOR_INDEX_OUT_OF_BOUNDS(index);
        RETERR;
    }

    char *removed_value = strdup(vector->arr[index]);
    free(vector->arr[index]);
    for (size_t i = index + 1; i < vector->size; i++)
    {
        vector->arr[i - 1] = vector->arr[i];
    }
    vector->size--;

    if (vector->size <= (vector->capacity / 2))
    {
        resize_vector_str(vector, 1);
    }

    return removed_value;
}

int vector_str_find_first_index_of(const vector_str *vector, const char *value)
{
    if (vector == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < vector->size; i++)
    {
        if (strcmp(vector->arr[i], value) == 0)
        {
            return i;
        }
    }

    return -1;
}

int vector_str_find_last_index_of(const vector_str *vector, const char *value)
{
    if (vector == NULL)
    {
        return -1;
    }

    if (vector->size == 0)
    {
        return -1;
    }

    for (size_t i = vector->size - 1; i >= 0; i--)
    {
        if (strcmp(vector->arr[i], value) == 0)
        {
            return i;
        }
    }

    return -1;
}

/* VECTOR_STR:END */
