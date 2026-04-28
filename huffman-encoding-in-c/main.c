#include <../huffman-encoding-in-c/error-codes.h>
#include <stdio.h>
#include <stdlib.h>

void process_error(int error_code);

int run_app(void)
{
    printf("%s\n", "Huffman Encoding w. C");
    printf("%s\n", "Initializing...");

    printf("%s", "Enter path to the file you want to encode: ");

    char *file_path = "";
    if (scanf("%s", file_path) != 1)
    {
        return INVALID_SCANF;
    }

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL)
    {
        return INVALID_FILE_PATH;
    }
}

int main(void)
{
    int result = run_app();
    if (result > 0)
    {
        process_error(result);
    }

    return 0;
}

void process_error(int error_code)
{
    switch (error_code)
    {
    case INVALID_SCANF:
        printf("%s", "Incorrect input");
        break;
    default:
        return;
    }

    return;
}
