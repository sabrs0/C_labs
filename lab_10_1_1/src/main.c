#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/funcs.h"
int main(int argc, char **argv)
{
    char in_file[FILE_MAX_SIZE];
    int action;
    void *data = NULL;
    void *key = NULL;
    node_t *head_list = NULL;
    node_t *ans_node = NULL;
    if (check_args(argc, argv, &action, in_file, &key))
    {
        free(key);
        return ERROR;
    }
    head_list = init_list(head_list, in_file);
    if (!head_list)
    {
        return ERROR;
    }
    printf("INITIALIZED LIST:\n");
    print_list(head_list);
    if (action == 1)
    {
        data = pop_front(&head_list);
        printf("ans = %s\n", (char*)data);
        printf("List after this action:\n");
        print_list(head_list);
        free(data);
        free_list(head_list);
    }
    else if (action == 2)
    {
        ans_node = find(head_list, key, comparator);
        printf("ans == %p\n", (void *)ans_node);
        free(key);
        free_list(head_list);
    }
    else if (action == 3)
    {
        ans_node = reverse(head_list);
        printf("new_head = %s\n", (char *)ans_node->data);
        print_list(ans_node);
        free_list(ans_node);
    }
    else if (action == 4)
    {
        head_list = sort(head_list, comparator);
        if (!head_list)
        {
            return ERROR;
        }
        printf("SORTED LIST:\n");
        print_list(head_list);
        free_list(head_list);
    }
    else
    {
        free_list(head_list);
        return ERROR;
    }
    return OK;
}
/*action:
1 - pop_front;
2 - find;
3 - reverse
4-sort;*/
