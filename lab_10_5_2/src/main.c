#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
int main()
{
    int action, index = -1;
    half_dyn_str *head = NULL, *str = NULL, *res = NULL;
    if (input_data(&action, &head, &str) == ERROR)
    {
        return ERROR;
    }
    if (action == OUT)
    {
        make_out(head);
    }
    else if (action == CAT)
    {
        make_cat(head, str, &res);
        make_out(res);
    }
    else if (action == SPS)
    {
        make_sps(&head);
        make_out(head);
    }
    else if (action == POS)
    {
        make_pos(head, str, &index);
        printf("%d\n", index);
    }
    free_list(res);
    free_list(head);
    free_list(str);
    return OK;
}

