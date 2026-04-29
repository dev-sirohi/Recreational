#include "appconsts.h"
#include "cvectors.h"
#include "exceptions.h"
#include <stdio.h>
#include <stdlib.h>

int encode_file_content(FILE *fp);

int run_app(void)
{
    printf("\n");
    printf("%s\n", "Huffman Encoding w. C");
    printf("%s\n", "Initializing...");
    printf("%s", "Enter path to the file you want to encode: ");

    char file_path[MAX_FILE_PATH_STR_SIZE];
    if (1 != scanf("%s", file_path))
    {
        ERR_IO_SCANF_INPUT_LEN;
        RETERR;
    }

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL)
    {
        ERR_IO_INVALID_FILE_PATH(file_path);
        RETERR;
    }

    encode_file_content(fp);

    return OK;
}

int main(void)
{
    run_app();

    return OK;
}

int encode_file_content(FILE *fp)
{
    return OK;
}
