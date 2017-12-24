#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* open_file(char* file_name, char* mode);
void close_file(FILE* file);
char* get_full_filename(char* path_to_file, char* file_name);
void rename_file(char* src, char* dest);
