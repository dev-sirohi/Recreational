#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE_SMALL 255

int runApp()
{
    int r_code = 0;
    // Accept path to file
    char* path = calloc(STR_SIZE_SMALL, sizeof(char));
    fgets(path, STR_SIZE_SMALL, stdin);

    FILE* file;
    file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Invalid file");
    }

    return r_code;
}

int main()
{
    runApp();
    return 0;
}
