#include "common.h"


void* common_safe_malloc(size_t size)
{
    void* p = malloc(size);
    if (p == NULL)
    {
        printf("Memory allocation error\n");
        exit(0);
    }
    return p;
}

FILE* common_file_safe_open(char* filePath, char* mode)
{
	FILE* file;
    file = fopen(filePath, mode);
    if (file == NULL)
    {
        printf("Error : Failed to open file - %s\n", filePath);
        exit(1);
    }
        
	return file;
}

int common_file_get_line_count(char* filePath, char* mode)
{       
    FILE* file = common_file_safe_open(filePath, mode);

    char * line = NULL;
    size_t len = 0;

	int lineCount = 0;
    while (getline(&line, &len, file) != -1) 
	{
		lineCount++;
    }

    if (line){
		free(line);
	}

    fclose(file);

    return lineCount;
}

DIR* common_directory_safe_open(char* directoryPath)
{
    DIR* directory = opendir(directoryPath);
    if (directory == NULL) {
        printf("Failed to open the directory.- %s\n", directoryPath);
        exit(1);
    }
    return directory;
}

int common_directory_get_file_count(char* directoryPath)
{
    int count = 0;

    DIR* directory = common_directory_safe_open(directoryPath);

    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) 
    {
        if (!strcmp (entry->d_name, ".") || !strcmp (entry->d_name, ".."))
            continue;

        count++;
    }

    closedir(directory);

    return count;
}

