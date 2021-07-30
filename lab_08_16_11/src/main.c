#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcs.h"
int main(int argc, char **argv)
{
    char in_file1[256];
    char in_file2[256];
    char out_file[256];
    int action;
    int check;
    
    if (check_args(argc, argv, in_file1, in_file2, out_file, &action))
    {
        return ERROR;
    }
    
    if (action == SUM)
    {
        check = make_sum(in_file1, in_file2, out_file);
        
        if (check)
        {
            return ERROR;
        }
    }
    
    if (action == MULT)
    {
        check = make_mult(in_file1, in_file2, out_file);
        
        if (check)
        {
            return ERROR;
        }
    }
    
    if (action == FIND_DET)
    {
        check = make_find_det(in_file1, out_file);
        
        if (check)
        {
            return ERROR;
        }
    }
    return OK;
}
