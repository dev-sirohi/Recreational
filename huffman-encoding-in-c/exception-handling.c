#include "exception-handling.h"
#include <stdio.h>

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
