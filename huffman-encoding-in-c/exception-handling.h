#ifndef HUFFMAN_ENCODING_ERROR_CODES
#define HUFFMAN_ENCODING_ERROR_CODES

#define OK 0

/* Process errors */
#define INVALID_SCANF 101

/* File management errors */
#define INVALID_FILE_PATH 2001

void process_error(int error_code);
int is_error(int return_value);

#endif
