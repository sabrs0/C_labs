#include <stdio.h>
#include "funcs.h"
#include <stdlib.h>
#include <string.h>
void pop_back(half_dyn_str **head)
{
    half_dyn_str *head_copy = *head;
    half_dyn_str *tmp;
    if ((*head)->next == NULL)
    {
        *head = NULL;
    }
    else
    {
        while ((*head)->next->next)	
        {
            *head = (*head)->next;
        }
        tmp = (*head)->next;
        (*head)->next = NULL;
        free(tmp);
        *head = head_copy;
    }
}
int find_node_len(half_dyn_str *node)
{
    int len = 0;
    while (node)
    {
        node = node->next;
        len++;
    }
    return len;
}
half_dyn_str *create_node(char data)
{
    half_dyn_str *tmp;
    tmp = malloc(sizeof(half_dyn_str));
    if (!tmp)
    {
        return NULL;
    }
    tmp->next = NULL;
    tmp->str_p = data;
    return tmp;
}
half_dyn_str *add_end(half_dyn_str *head, half_dyn_str *tmp)
{
    half_dyn_str *cur;
    if (!head)
        return tmp;
    cur = head;
    for (; cur->next; cur = cur->next);
    cur->next = tmp;
    return head;
}
void free_list(half_dyn_str *head)
{
    half_dyn_str *next;
    for (;head; head = next)
    {
        next = head->next;
        free(head);		
    }
}
int input_data(int *action, half_dyn_str **head, half_dyn_str **str)
{
    char piece;
    char action_str[4];
    if (!scanf("%s", action_str))
    {
        return ERROR;
    }
    if (!strcmp(action_str, "out"))
    {
        *action = OUT;
    }
    else if (!strcmp(action_str, "cat"))
    {
        *action = CAT;
    }
    else if (!strcmp(action_str, "sps"))
    {
        *action = SPS;
    }
    else if (!strcmp(action_str, "pos"))
    {
        *action = POS;
    }
    else
    {
        return ERROR;
    }
    half_dyn_str *tmp = NULL;
    scanf("%c", &piece);
    while (1)
    {
        if (scanf("%c", &(piece)) != 1)
        {
            free_list(*head);
            return ERROR;
        }
        if (piece == '\n')
        {
            piece = '\0';
            tmp = create_node(piece);
            if (!tmp)
            {
                free_list(*head);
                return ERROR;
            }
            *head = add_end(*head, tmp);
            break;
        }
        tmp = create_node(piece);
        if (!tmp)
        {
            free_list(*head);
            return ERROR;
        }
        *head = add_end(*head, tmp);
    }
    if (*action == POS || *action == CAT)
    {
        while (1)
        {
            if (scanf("%c", &(piece)) != 1)
            {
                free_list(*head);
                free_list(*str);
                return ERROR;
            }
            if (piece == '\n')
            {
                piece = '\0';
                tmp = create_node(piece);
                if (!tmp)
                {
                    free_list(*head);
                    free_list(*str);
                    return ERROR;
                }
                *str = add_end(*str, tmp);
                break;
            }
            *str = add_end(*str, create_node(piece));
        }	
    }
    if (*action == CAT)
    {
        pop_back(head);
    }
    return OK;
}
void make_out(half_dyn_str *head)
{
    while (head->next)
    {
        printf("%c", head->str_p);
        head = head->next;
    }
}
void make_cat(half_dyn_str *first, half_dyn_str *second, half_dyn_str **res)
{
    while (first)
    {
        *res = add_end(*res, create_node(first->str_p));
        first = first->next;
    }
    while (second)
    {
        *res = add_end(*res, create_node(second->str_p));
        second = second->next;
    }
}
void make_sps(half_dyn_str **head)
{
    half_dyn_str *head_copy = *head;
    half_dyn_str *tmp;
    half_dyn_str *tmp2;
    while ((*head)->next)
    {
        if ((*head)->str_p == ' ')
        {
            tmp = (*head)->next;
            while (1)
            {
                if (tmp)
                {
                    if (tmp->str_p != ' ')
                    {
                        (*head)->next = tmp;
                        break;
                    }
                }
                else
                {
                    tmp2 = (*head)->next;
                    free(tmp2);
                    (*head)->next = NULL;
                    break;
                }
                tmp2 = tmp;
                tmp = tmp->next;
                free(tmp2);
            }
        }
        (*head) = (*head)->next;
    }
    *head = head_copy;
}
int get_ind_by_node(half_dyn_str *head, half_dyn_str *cur)
{
    int index = 0;
    while (head != cur)
    {
        index ++;
        head = head->next;
    }
    return index;
}
void make_pos(half_dyn_str *head, half_dyn_str *str, int *index)
{	
    half_dyn_str *head_str = str;
    half_dyn_str *head_main = head;
    half_dyn_str *tmp_main;
    int flag;
    while (head)
    {
        flag = 0;
        if (find_node_len(head) >= find_node_len(str))
        {
            tmp_main = head;
            *index = get_ind_by_node(head_main, head);
            while (str)
            {
                if (str->str_p != tmp_main->str_p && str->str_p != '\0')
                {
                    str = head_str;
                    flag = 1;
                    break;
                }
                str = str->next;
                tmp_main = tmp_main->next;
            }
            if (!flag)
            {
                break;
            }
        }
        else
        {
            *index = -1;
            break;
        }
        head = head->next;
    }
    if (flag == 1)
    {
        *index = -1;
    }
}
