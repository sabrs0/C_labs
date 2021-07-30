#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "funcs.h"
int comparator(const void *x1, const void *x2)
{
    int v1, v2;
    v1 = *(int*)x1;
    v2 = *(int*)x2;
    
    if (v1 < v2)
        return -1;
    else if (v1 == v2)
        return 0;
    
    return 1;
}
void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *))
{
    char *new_el = malloc(size); 
    int index;
    char *arr = (char *)first;
    
    for (size_t i = 1; i < number; i++)
    {
        memmove(new_el, arr + i * size, size);
        index = i - 1;
        
        while (index >= 0 && comparator((arr + index * size), new_el) > 0)
        {
            memmove(arr + index * size + 1 * size, arr + index * size, size);
            memmove(arr + index * size, new_el, size);
            index = index - 1;
        }
        
        memmove(arr + index * size + 1 * size, new_el, size);
    }
    
    free(new_el);
}
int key(int *pb_src, int *pe_src, int **pb_dst, int **pe_dst)
{
    if (!pb_src)
        return ERR_INVALID_PTR;
    
    int m = 0;
    int *tmp;
    
    for (int *i = pb_src; i < pe_src; i ++)
    {    
        if (*i > 0)
        {
            m ++;
        }
        else
            break;
    }
    
    if (!m)
    {
        return ERROR;
    }
    
    tmp = malloc(sizeof(int) * m);
    
    if (tmp)
        *pb_dst = tmp;
    else
    {
        return ERR_INVALID_PTR;
    }
    
    for (int i = 0; i < m; i ++)
    {
        *(*pb_dst + i) = *(pb_src + i);
    }
    
    //*pb_dst = pb_src;
    *pe_dst = *pb_dst + m;
    return OK;
}

int checking_args(int argc, char *argv[], char *in_file, char *out_file)
{
    if (argc != 3 && argc != 4)
    {
        printf("ERROR in argc\n");
        return ERROR;
    }
    
    if (argc == 4 && strcmp(argv[3], "f"))
    {
        printf("ERROR in [f]\n");
        return ERROR;
    }
    
    strcpy(in_file, argv[1]);
    strcpy(out_file, argv[2]);
    return OK;
}
int checking_data(char in_file[], int *n)
{
    FILE *f;
    int check_input, x;
    f = fopen(in_file, "r");
    
    if (!f)
    {
        return ERROR;
    }
    
    while (1)
    {
        check_input = fscanf(f, "%d", &x);
        
        if (check_input == EOF)
            break;
        
        if (check_input != 1)
        {
            return ERROR;
        }
        
        *n = *n + 1;
    }
    
    if (fclose(f) == EOF)
        return ERROR;
    
    if (*n == 0)
        return ERROR;
    
    return OK;
}
int create_array(int n, int **arr_head, int **arr_tail)
{
    int *tmp;
    tmp = malloc(sizeof(int) * n);
    
    if (!tmp)
    {
        return ERROR;
    }
    
    *arr_head = tmp;
    *arr_tail = *arr_head + n;
    return OK;
}
int init_array(char in_file[], int *arr_head)
{
    FILE *f;
    int x;
    f = fopen(in_file, "r");
    
    if (!f)
    {
        return ERROR;
    }
    
    for (int i = 0; fscanf(f, "%d", &x) != EOF; i ++)
    {
        *(arr_head + i) = x;
    }
    
    if (fclose(f) == EOF)
    {
        return ERROR;
    }
    
    return OK;
}
int output_array(char out_file[], int *arr_new_head, int *arr_new_tail)
{
    FILE *f2;
    f2 = fopen(out_file, "w");
    
    if (!f2)
    {
        return ERROR;
    }
    
    for (int *i = arr_new_head; i < arr_new_tail; i ++)
    {
        fprintf(f2, "%d ", *i);
    }
    
    if (fclose(f2))
        return ERROR;
    
    return OK;
}
