#ifndef HUFFMAN_ENCODING_ERROR_CODES
#define HUFFMAN_ENCODING_ERROR_CODES

#define OK 0
#define RETOK exit(EXIT_SUCCESS)
#define RETERR exit(EXIT_FAILURE)

#define BASIC_ERR_FORMAT "\nErr::START\n\tFile: %s\n\tLine: %d\n\tMsg: %s\nErr::END\n"

/* IO ERR */
#define ERR_IO_SCANF_INPUT_LEN                                                                     \
    fprintf(stderr, BASIC_ERR_FORMAT, __FILE__, __LINE__, "Invalid input for scanf")

#define ERR_IO_INVALID_FILE_PATH(invalid_file_path)                                                \
    fprintf(stderr,                                                                                \
            "\nErr::START\n\tFile: %s\n\tLine: %d\n\tMsg: Invalid file path: %s\nErr::END\n",      \
            __FILE__,                                                                              \
            __LINE__,                                                                              \
            invalid_file_path)

#endif
