#include "app-constants.h"
#include "exception-handling.h"
#include <stdio.h>
#include <stdlib.h>

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
