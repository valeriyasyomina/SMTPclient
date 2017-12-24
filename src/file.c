#include "file.h"

FILE* open_file(char* file_name, char* mode)
{
	if (!file_name)
	{
		printf("Null file name\n");
		return NULL;
	}
	if (!mode)
	{
		printf("Null mode\n");
		return NULL;
	}

	FILE* file = fopen(file_name, mode);

	if (!file)
	{
		printf("Null file\n");
		return NULL;
	}
	return file;
}

void close_file(FILE* file)
{
	if (file)
	{
		fclose(file);
	}
}

char* get_full_filename(char* path_to_file, char* file_name)
{
	if (!path_to_file)
		return NULL;
	if (!file_name)
		return NULL;

	int path_to_file_size = strlen(path_to_file);
	int buffer_size = path_to_file_size + strlen(file_name) + 1;

	char* buffer = (char*) malloc(buffer_size);
	strncpy(buffer, path_to_file, path_to_file_size);
	strcat(buffer, file_name);
	buffer[buffer_size - 1] = '\0';
	return buffer;
}

void rename_file(char* src, char* dest)
{
	if (src && dest)
	{
		rename(src, dest);
	}
}