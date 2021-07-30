#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"
int main(int argc, char **argv)
{
    films_t *films = NULL;
    films_t *films_filtered = NULL;
    int filtered_ind = 0;
    FILE *f;
    char in_file[MAX_FILE_NAME] = "in.txt";
    int field;
    int find_flag = 0;
    char *key = NULL;
    int len = 0;
    
    if (check_args(argc, argv, in_file, &field, &key))
    {
        free(key);
        return ERROR;
    }
    f = fopen(in_file, "r");
    
    if (!f)
    {
        return ERROR;
    }
    
    if (count_len(&len, f))
    {
        return ERROR;
    }

    if (fclose(f) == EOF)
    {
        return ERROR;
    }
    f = fopen(in_file, "r");
    
    if (!f)
    {
        return ERROR;
    }
    
    if (scan_films(f, &films, field, len))
    {
        free_struct(&films, len);
        free(key);
        return ERROR;
    }

    if (fclose(f) == EOF)
    {
        return ERROR;
    }
    
    if (argc == 3)
    {
        print_films(films, len);
    }	
    else
    {
        films_filtered = search_elems(films, len, field, key, &filtered_ind, &find_flag);
		
        if (!films_filtered)
        {
            if (!find_flag)
            {
                free_struct(&films, len);
                free(key);
                return ERROR;
            }
            else
            {
                free_struct(&films, len);
                free(key);
                return OK;
            }
        }
        else
        {
            print_films(films_filtered, filtered_ind);
            free_struct(&films_filtered, len);
        }
    }    
    free_struct(&films, len);
    free(key);
    return OK;
}
