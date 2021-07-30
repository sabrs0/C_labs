#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include "funcs.h"
#define EPS 0.00000001
#define OK 0
#define ERROR 1
#define FILE_MAX_SIZE 255
#define PREFIX_SIZE 26
void print_array_by_prefix(item_info item_arr[], int n, char prefix[])
{
    for (int i = 0; i < n; i ++)
    {
        if (strncmp(item_arr[i].name, prefix, strlen(prefix)) == 0)
            printf("%s\n%.6lf\n%.6lf\n", item_arr[i].name, item_arr[i].mass, item_arr[i].value);
    }
}
void print_array(item_info item_arr[], int n)
{
    for (int i = 0; i < n; i ++)
    {
        printf("%s\n%.6lf\n%.6lf\n", item_arr[i].name, item_arr[i].mass, item_arr[i].value);
    }
}
void fill_array(item_info item_arr[], FILE *f)
{
    int i = 0;

    while (1)
    {
        if (fscanf(f, "%s", item_arr[i].name) == EOF)
            break;
        fscanf(f, "%lf", &item_arr[i].mass);
        fscanf(f, "%lf", &item_arr[i].value);
        item_arr[i].density = item_arr[i].mass / item_arr[i].value;
        i ++;
    }
}
int create_array(item_info **arr, int n)
{
    item_info *tmp;
    tmp = malloc(sizeof(item_info) * n);

    if (!tmp)
    {
        free(tmp);
        return ERROR;
    }
    else
        *arr = tmp;
    return OK;
}
int check_input(FILE *f, item_info item, int *n, char filename[])
{
    int input;
    f = fopen(filename, "r");

    if (!f)
    {
        return ERROR;
    }

    while (1)
    {
        //input = fscanf(f, "%s%lf%lf", item.name, &item.mass, &item.value);
        input = fscanf(f, "%s", item.name);

        if (input == EOF)
            break;

        if (input != 1)
            return ERROR;

        if (strlen(item.name) > 25)
            return ERROR;

        input = fscanf(f, "%lf", &item.mass);

        if (input != 1)
            return ERROR;

        input = fscanf(f, "%lf", &item.value);

        if (input != 1)
            return ERROR;

        if (item.mass <= 0 || item.value <= 0)
        {
            return ERROR;
        }

        *n = *n + 1;
    }

    if (fclose(f) == EOF)
    {
        return ERROR;
    }

    if (*n > 15 || *n == 0)
        return ERROR;

    return OK;
}
int comparator(const void *x1, const void *x2)
{
    item_info v1, v2;
    v1 = *(item_info*)x1;
    v2 = *(item_info*)x2;

    if (fabs(v1.density - v2.density) < EPS)
        return 0;
    else if (v1.density < v2.density)
        return -1;
    return 1;
}
int checking_arguments(int argc, char *argv[], char *filename, char *prefix)
{
    if (argc < 2 || argc > 3)
    {
        return ERROR;
    }
    strcpy(filename, argv[1]);

    if (argc == 3)
    {
        if (strlen(argv[2]) > 25)
            return ERROR;
        strcpy(prefix, argv[2]);
    }
    else
        strcpy(prefix, "");
    return OK;
}
