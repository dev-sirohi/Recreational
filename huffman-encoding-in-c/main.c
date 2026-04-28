#include "app-constants.h"
#include "error-codes.h"
#include <stdio.h>
#include <stdlib.h>

/* FUNCTION DECLARATIONS */

void process_error(int error_code);
int is_error(int return_value);

/* GLOBAL VARIABLES */

static int F_RES = 0;

/* API */

int encode_file_content()
{

    return OK;
}

int run_app(void)
{
    printf("%s\n", "Huffman Encoding w. C");
    printf("%s\n", "Initializing...");
    printf("%s", "Enter path to the file you want to encode: ");

    char file_path[MAX_FILE_PATH_STR_SIZE];
    if (scanf("%s", file_path) != 1)
    {
        return INVALID_SCANF;
    }

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL)
    {
        return INVALID_FILE_PATH;
    }

    F_RES = encode_file_content(fp);
    if (is_error(F_RES))
    {
        return F_RES;
    }

    return OK;
}

int main(void)
{
    int result = run_app();
    if (result > 0)
    {
        process_error(result);
    }

    return OK;
}

int is_error(int return_value)
{
    int error_codes[] = {
        INVALID_SCANF,
        INVALID_FILE_PATH,
    };

    size_t error_codes_arr_length = sizeof(error_codes) / sizeof(int);
    for (size_t i = 0; i < error_codes_arr_length; i++)
    {
        if (error_codes[i] == return_value)
        {
            return 1;
        }
    }

    return OK;
}

void process_error(int error_code)
{
    printf("\n");
    printf("%s\n", "ERR::");
    printf("%s", "     ");
    int count = 0;
    switch (error_code)
    {
    case INVALID_SCANF:
        ++count;
        printf("%d. %s\n", count, "Incorrect input");
        break;
    case INVALID_FILE_PATH:
        ++count;
        printf("%d. %s\n", count, "Invalid file path");
        break;
    default:
        return;
    }
    printf("EXITING::WITH_CODE::%d", error_code);

    return;
}
