#include <stdlib.h>
int fill_fib(int *arr, int n)
{
    if (n <= 0)
    {
        return -1;
    }
    int fib = 2, a = 1,b = 1;
    for (int i = 0; i < n; i ++)
    {
        if (i == 0)
        {
            arr[i] = 0;
        }
        else if (i == 1 || i == 2)
        {
            arr[i] = 1;
        }
        else
        {
            arr[i] = fib;
            b = a;
            a = fib;
            fib = fib + b;
        }
    }
    return 0;
}
int find_len(int *arr1, int n)
{
    int new_len = 0;
    int *arr3;
    arr3 = malloc(sizeof(int) * n);
    if (!arr3)
    {
        return -1;
    }
    int flag;
    for (int i = 0; i < n; i ++)
    {
        flag = 0;
        for (int j = 0; j < new_len; j ++)
        {
            if (arr3[j] == arr1[i])
            {	
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            arr3[new_len] = arr1[i];
            new_len ++;
        }
    }
    return new_len;
}
int fill_penetr(int *arr1, int *arr2, int n, int new_len)
{
    int *arr3;
    arr3 = malloc(sizeof(int) * n);
    if (!arr3)
    {
        return -1;
    }
    int flag;
    int ind2 = 0;
    for (int i = 0; i < n; i ++)
    {
        flag = 0;
        for (int j = 0; j < ind2; j ++)
        {
            if (arr3[j] == arr1[i])
            {	
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            arr3[ind2] = arr1[i];
            ind2 ++;
        }
    }
    for (int i = 0; i < ind2; i ++)
    {
        for (int j = 0; j < n; j ++)
        {
            if (arr1[j] == arr3[i])
            {
                arr2[i] = j;
                break;
            }
        }
    }
    return 0;
}
