#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include "funcs.h"
#define EPS 0.0001
#define OK 0
#define ERROR 1
#define FILE_MAX_SIZE 255
#define PREFIX_SIZE 26
int main(int argc, char *argv[])
{
    item_info item;
    char filename[FILE_MAX_SIZE];
    char prefix[PREFIX_SIZE];
    item_info *item_arr;
    FILE *f = NULL;
    int n = 0;

    if (checking_arguments(argc, argv, filename, prefix))
        return ERROR;

    if (check_input(f, item, &n, filename))
        return ERROR;

    if (create_array(&item_arr, n))
        return ERROR;

    f = fopen(filename, "r");

    if (!f)
    {
        return ERROR;
    }

    fill_array(item_arr, f);

    if (!strcmp(prefix, "ALL"))
    {
        print_array(item_arr, n);
    }
    else if (!strcmp(prefix, ""))
    {
        qsort(item_arr, n, sizeof(item_info), comparator);
        print_array(item_arr, n);
    }
    else
    {
        print_array_by_prefix(item_arr, n, prefix);
    }
    if (fclose(f) == EOF)
    {
        free(item_arr);
        return ERROR;
    }

    free(item_arr);
    return OK;
}
