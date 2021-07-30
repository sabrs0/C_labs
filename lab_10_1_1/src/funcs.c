#define _GNU_SOURCE	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/funcs.h"
int comparator(const void *v1, const void *v2)
{
    return (strcmp((char*)v1, (char*)v2));	
}
int check_args(int argc, char **argv, int *action, char filename[], void **key)
{
    if (argc != 3 && argc != 4)
    {
        return ERROR;
    }
    if (!strcmp("pop_front", argv[2]))
    {
        *action = 1;
    }
    else if (!strcmp("find", argv[2]))
    {
        *action = 2;
    }
    else if (!strcmp("reverse", argv[2]))
    {
        *action = 3;
    }
    else if (!strcmp("sort", argv[2]))
    {
        *action = 4;
    }
    else
    {
        return ERROR;
    }
    if (*action == 2)
    {
        if (argc != 4)
            return ERROR;
        *key = (char *)malloc(sizeof(char) * (strlen(argv[3]) + 1));
        if (!*key)
            return ERROR;
        memmove(*key, argv[3], sizeof(char) * (strlen(argv[3]) + 1));
    }
    else
    {
        if (argc != 3)
            return ERROR;
    }
    strcpy(filename, argv[1]);
    return OK;
}
int find_node_len(node_t *node)
{
    int len = 0;
    while (node)
    {
        node = node->next;
        len++;
    }
    return len;
}
node_t *create_node(char *data)
{
    node_t *tmp;
    tmp = malloc(sizeof(node_t));
    if (!tmp)
    {
        return NULL;
    }
    tmp->next = NULL;
    tmp->data = (char*)malloc(sizeof(char) * (strlen(data) + 1));
    if (!tmp->data)
    {
        free(tmp);
        return NULL;
    }
    memmove(tmp->data, data, sizeof(char) * (strlen(data) + 1));
    return tmp;
}
node_t *add_end(node_t *head, node_t *tmp)
{
    node_t *cur;
    if (!head)
        return tmp;
    cur = head;
    for (; cur->next; cur = cur->next);
    cur->next = tmp;
    return head;
}
void front_back_split(node_t *head, node_t **back)
{
    int len;
    node_t *head_list = head;
    len = find_node_len(head);
    for (int i = 0; i < len / 2 + len % 2 - 1; i ++)
    {
        head = head->next;
    }
    if (head)
    {
        *back = head->next;
        head->next = NULL;
        head = head_list;
    }
}
int copy_mem_str(void **from, void *to)
{
    char *tmp = (char *)to;
    free(*from);
    *from = (char*)malloc(sizeof(char) * (strlen(tmp) + 1));
    if (!*from)
        return ERROR;
    if (!memmove(*from, to, sizeof(char) * (strlen(tmp) + 1)))
        return ERROR;
    return OK;
}
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *x1, const void *x2))
{
    node_t *united_node = NULL;
    node_t **united_head = &united_node;
    while (*head_a || *head_b)
    {
        if (*head_a)
        {
            if (*head_b)
            {
                if (comparator((*head_a)->data, (*head_b)->data) < 0)
                {
                    *united_head = *head_a;
                    *head_a = (*head_a)->next;
                }
                else
                {
                    *united_head = *head_b;
                    *head_b = (*head_b)->next;
                }
            }
            else
            {
                *united_head = *head_a;
                *head_a = (*head_a)->next;
            }
        }
        else if (*head_b)
        {
            *united_head = *head_b;
            *head_b = (*head_b)->next;
        }
        united_head = &((*united_head)->next);
    }
    return united_node;
}
node_t *sort(node_t *head, int (*comparator)(const void *x1, const void *x2))
{
    node_t *second = NULL;
    node_t *first = NULL;
    if (find_node_len(head) > 1 && head)
    {
        first = head;
        front_back_split(first, &second);
        first = sort(first, comparator);
        second = sort(second, comparator);
        head = sorted_merge(&first, &second, comparator);
    }
    return head;
}
node_t *reverse(node_t *head)
{
    node_t *cur = head;
    node_t *new_head = head;
    node_t *next_cur;
    int len = find_node_len(head);
    for (int i = 0; i < len - 1; i ++)
    {
        next_cur = cur->next;
        cur->next = next_cur->next;
        next_cur->next = new_head;
        new_head = next_cur;
    }
    return new_head;
}
node_t *find(node_t *head, void *data, int (*comparator)(const void *x1, const void *x2))
{
    node_t *tmp;
    tmp = head;
    while (tmp)
    {
        if (comparator(tmp->data, data) == 0)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return tmp;
}
void *pop_front(node_t **head)
{
    void *elem = NULL;
    node_t *tmp = NULL;
    if (head != NULL && *head != NULL)
    {
        elem = (*head)->data;
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
    return elem;
}
node_t *init_list(node_t *head, char filename[])
{
    char *string = NULL;
    size_t len_s = 0;
    node_t *tmp = NULL;
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        return NULL;
    }
    while (getline(&string, &len_s, f) != -1)
    {
        string[strlen(string) - 1] = '\0';
        tmp = create_node(string);
        head = add_end(head, tmp);
        free(string);
        string = NULL;
        len_s = 0;
    }
    free(string);
    fclose(f);
    return head;
}
int print_list(node_t *head)
{
    while (head != NULL)
    {
        printf("%s\n", (char*)head->data);
        head = head->next;
    }
    return OK;
}
void free_list(node_t *head)
{
    node_t *next;
    for (; head; head = next)
    {
        next = head->next;
        free(head->data);
        free(head);		
    }
}
