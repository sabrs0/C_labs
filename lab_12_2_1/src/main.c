#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <dlfcn.h>
#include "funcs.h"
int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    int *arr_head = NULL, *arr_tail, *arr_new_head = NULL, *arr_new_tail;
    char in_file[FILE_MAX_SIZE], out_file[FILE_MAX_SIZE];
    int n = 0;
    
    if (checking_args(argc, argv, in_file, out_file))
    {
        return ERROR;
    }
    
    if (checking_data(in_file, &n))
    {
        return ERROR;
    }
    
    if (create_array(n, &arr_head, &arr_tail))
    {
        free(arr_head);
        return ERROR;
    }
    
    if (init_array(in_file, arr_head))
    {
        free(arr_head);
        return ERROR;
    }
    
    if (argc == 4)
    {
        if (key(arr_head, arr_tail, &arr_new_head, &arr_new_tail))
        {
            free(arr_head);
            return ERROR;
        }
    }
    else
    {   
        if (create_array(n, &arr_new_head, &arr_new_tail))
        {
            free(arr_head);
            free(arr_new_head);
            return ERROR;
        }
        
        for (int i = 0; i < n; i ++)
        {
            *(arr_new_head + i) = *(arr_head + i);
        }
    }

    mysort(arr_new_head, (arr_new_tail - arr_new_head), sizeof(int), comparator);
    
    if (output_array(out_file, arr_new_head, arr_new_tail))
    {
        free(arr_head);
        free(arr_new_head);
        return ERROR;
    }

    free(arr_head);
    free(arr_new_head);
    return OK;
}

