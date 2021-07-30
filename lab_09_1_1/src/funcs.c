#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"
int powering(int a, int power)
{
    int mnoj = a;
    int res = 1;
    
    for (int i = 0; i < power ; i ++)
    {
        res = res * mnoj;
    }
    return res;
}
void free_struct(films_t **films, int len)
{
    for (int i = 0; i < len; i ++)
    {
        free((*films)[i].title);
        free((*films)[i].name);
    }
    free(*films);
}
void itoa(int numb, char *string)
{
    int len = 0;
    int numb_copy = numb;
    
    while (numb_copy)
    {
        len++;
        numb_copy /= 10;
    }
    
    for (int i = 0; i < len ; i ++)
    {
        string[i] = (numb / powering(10, len - i - 1)) % powering(10, 1) + 48;
    }
    string[len] = '\0';
}
int check_args(int argc, char **argv, char in_file[], int *field, char **key)
{
    if (argc != 3 && argc != 4)
    {
        return ERROR;
    }
    
    if (!strcmp(argv[2], "title"))
    {
        *field = 1;
    }
    else if (!strcmp(argv[2], "name"))
    {
        *field = 2;
    }
    else if (!strcmp(argv[2], "year"))
    {
        *field = 3;
    }
    else
    {
        return ERROR;
    }
    strcpy(in_file, argv[1]);
    
    if (argc == 4)
    {
        if (!strcmp(argv[2], "year"))
        {
            for (int i = 0; i < strlen(argv[3]); i ++)
            {
                if (argv[3][i] < '0' || argv[3][i] > '9')
                {
                    return ERROR;
                }
            }
        }
        *key = (char*)malloc(sizeof(char) * (strlen(argv[3]) + 1));
        
        if (*key == NULL)
        {
            return ERROR;
        }
        strcpy(*key, argv[3]);
    }
    return OK;
}
int bin_search(films_t *films, int field, char *key, int *search_ind, int len)
{
    int left_i = 0;
    int right_i = len - 1;
    int search = 0;
    int mid;
    char comp_fig[5];
    
    if (field == 1)
    { 
        while (left_i <= right_i)
        {
            mid = (right_i + left_i) / 2;
            
            if (!strcmp((films + mid)->title, key))
            {
                search = 1;
                *search_ind = mid;
                break;
            }
            else if (strcmp((films + mid)->title, key) < 0)
            {
                left_i = mid + 1;
            }
            else
            {
                right_i = mid - 1;
            }
        }
        
        if (!search)
        {
            return ERROR;
        }
    }
    else if (field == 2)
    {
        while (left_i <= right_i)
        {
            mid = (right_i + left_i) / 2;
            
            if (!strcmp((films + mid)->name, key))
            {
                search = 1;
                *search_ind = mid;
                break;
            }
            else if (strcmp((films + mid)->name, key) < 0)
            {
                left_i = mid + 1;
            }
            else
            {
                right_i = mid - 1;
            }
        }
        if (!search)
        {
            return ERROR;
        }
    }   
    else
    {
        while (left_i <= right_i)
        {
            mid = (right_i + left_i) / 2;
            itoa((films + mid)->year, comp_fig);
            
            if (!strcmp(comp_fig, key))
            {
                search = 1;
                *search_ind = mid;
                break;
            }
            else if (strcmp(comp_fig, key) < 0)
            {
                left_i = mid + 1;
            }
            else
            {
                right_i = mid - 1;
            }
        }
        
        if (!search)
        {
            return ERROR;
        }
    }
    return OK;
}
int count_len(int *len, FILE *f)
{
    char *title_line = NULL;
    size_t leng_title = 0;
    char *name_line = NULL;
    size_t leng_name = 0;
    int year_line;
    char n;
    *len = 0;
    
    for (int i = 0; ; i ++)
    {    
        if (getline(&title_line, &leng_title, f) == -1)
        {
            free(title_line);
            if (i == 0)
                return ERROR;
            break;
        }
        
        if (!strcmp(title_line, "\n"))
        {
            free(title_line);
            leng_title = 0;
            leng_name = 0;
            return ERROR;
        }
        
        if (getline(&name_line, &leng_name, f) == -1)
        {
            leng_title = 0;
            leng_name = 0;
            free(title_line);
            return ERROR;
        }
        
        if (!strcmp(name_line, "\n"))
        {
            leng_title = 0;
            leng_name = 0;
            free(title_line);
            free(name_line);
            return ERROR;
        }
        
        if (fscanf(f, "%d", &year_line) != 1)
        {
            leng_title = 0;
            leng_name = 0;
            free(title_line);
            free(name_line);
            return ERROR;
        }
        
        if (year_line < 0)
        {
            leng_title = 0;
            leng_name = 0;
            free(title_line);
            free(name_line);
            return ERROR;
        }
        
        if (fscanf(f, "%c", &n) == 1)
        {
            if (n != '\n')
            {
                leng_title = 0;
                leng_name = 0;
                free(title_line);
                free(name_line);
                return ERROR;
            }
        }
        free(title_line);
        free(name_line);
        title_line = NULL;
        name_line = NULL;
        leng_title = 0;
        leng_name = 0;
        (*len) ++;
    }
    return OK;
}
int move_right(films_t **films, int index, int len)
{
    char *tmp;
    
    for (int i = len - 1; i >= index + 1; i --)
    {
        tmp = (char*)malloc(sizeof(char) * (strlen((*films + (i - 1))->title) + 1));
        
        if (tmp == NULL)
        {
            return ERROR;
        }
        free((*films + (i))->title);
        (*films + (i))->title = tmp;
        strcpy((*films + (i))->title, ((*films + (i - 1))->title));
        tmp = (char*)malloc(sizeof(char) * (strlen((*films + (i - 1))->name) + 1));
        
        if (tmp == NULL)
        {
            return ERROR;
        }
        free((*films + (i))->name);
        (*films + (i))->name = tmp;
        strcpy((*films + (i))->name, (*films + (i - 1))->name);
        (*films + (i))->year = (*films + (i - 1))->year;
    }
    return OK;
}
int scan_films(FILE *f, films_t **films, int field, int len)
{
    films_t *tmp;
    char *title_line = NULL;
    size_t leng_title = 0;
    char *name_line = NULL;
    size_t leng_name = 0;
    int year_line;
    char n;
    int index;
    tmp = malloc(sizeof(films_t) * len);
    
    if (!tmp)
    {
        return ERROR;
    }
    *films = tmp;
    
    for (int i = 0; i < len; i ++)
    {
        (*films + i)->title = NULL;
        (*films + i)->name = NULL;
    }
    
    for (int i = 1; ;i ++)
    {
        if (getline(&title_line, &leng_title, f) == -1)
        {
            free(title_line);
            if (i == 1)
                return ERROR;
            break;
        }
        
        if (!strcmp(title_line, "\n"))
        {
            free(title_line);
            leng_title = 0;
            leng_name = 0;
            return ERROR;
        }
        
        if (getline(&name_line, &leng_name, f) == -1)
        {
            leng_title = 0;
            leng_name = 0;
            free(title_line);
            return ERROR;
        }
        
        if (!strcmp(name_line, "\n"))
        {
            leng_title = 0;
            leng_name = 0;
            free(title_line);
            free(name_line);
            return ERROR;
        }
        
        if (fscanf(f, "%d", &year_line) != 1)
        {
            leng_title = 0;
            leng_name = 0;
            free(title_line);
            free(name_line);
            return ERROR;
        }
        
        if (year_line < 0)
        {
            leng_title = 0;
            leng_name = 0;
            free(title_line);
            free(name_line);
            return ERROR;
        }
        
        if (fscanf(f, "%c", &n) == 1)
        {
            if (n != '\n')
            {
                leng_title = 0;
                leng_name = 0;
                free(title_line);
                free(name_line);
                return ERROR;
            }
        }
        
        if (i == 1)
        {
            title_line[strlen(title_line) - 1] = '\0';
            leng_title --;
            (*films + (i - 1))->title = (char*)malloc(sizeof(char) * (strlen(title_line) + 1));
            
            if ((*films + (i - 1))->title == NULL)
            {
                leng_title = 0;
                leng_name = 0;
                free(title_line);
                free(name_line);
                return ERROR;
            }
            strcpy((*films + (i - 1))->title, title_line);
            name_line[strlen(name_line) - 1] = '\0';
            leng_name --;            
            (*films + (i - 1))->name = (char*)malloc(sizeof(char) * (strlen(name_line) + 1));
            
            if ((*films + (i - 1))->name == NULL)
            {
                leng_title = 0;
                leng_name = 0;
                free(title_line);
                free(name_line);
                return ERROR;
            }
            strcpy((*films + (i - 1))->name, name_line);
            (*films + (i - 1))->year = year_line;
            
            if ((*films + (i - 1))->year < 0 || (*films + (i - 1))->year > 2020)
            {
                leng_title = 0;
                leng_name = 0;
                free(title_line);
                free(name_line);
                return ERROR;
            }   
        }
        else
        {
            
            if (field == 1)
            {
                index = i - 1;
                title_line[strlen(title_line) - 1] = '\0';
                leng_title --;
                
                for (int j = 0; j < i - 1; j ++)
                {
                    if (strcmp(title_line, (*films + (j))->title) < 0)
                    {
                        index = j;
                        break;
                    }
                }
                
                if (move_right(films, index, i))
                {
                    leng_title = 0;
                    leng_name = 0;
                    free(title_line);
                    free(name_line);
                    return ERROR;
                }
                free((*films + (index))->title);
                (*films + (index))->title = (char*)malloc(sizeof(char) * (strlen(title_line) + 1));
                
                if ((*films + (index))->title == NULL)
                {
                    leng_title = 0;
                    leng_name = 0;
                    free(title_line);
                    free(name_line);
                    return ERROR;
                }
                strcpy((*films + (index))->title, title_line);
                name_line[strlen(name_line) - 1] = '\0';
                leng_name --;
                free((*films + (index))->name);
                (*films + (index))->name = (char*)malloc(sizeof(char) * (strlen(name_line) + 1));
                
                if ((*films + (index))->name == NULL)
                {
                    leng_title = 0;
                    leng_name = 0;
                    free(title_line);
                    free(name_line);
                    return ERROR;
                }
                strcpy((*films + (index))->name, name_line);
                (*films + (index))->year = year_line;
                
                if ((*films + (index))->year < 0)
                {
                    leng_title = 0;
                    leng_name = 0;
                    free(title_line);
                    free(name_line);
                    return ERROR;
                }
            }
            else if (field == 2)
            {
                name_line[strlen(name_line) - 1] = '\0';
                leng_name --;
                index = i - 1;
                
                for (int j = 0; j < i - 1; j ++)
                {
                    if (strcmp(name_line, (*films + (j))->name) < 0)
                    {
                        index = j;
                        break;
                    }
                }
                
                if (move_right(films, index, i))
                {
                    leng_title = 0;
                    leng_name = 0;
                    free(title_line);
                    free(name_line);				
                    return ERROR;
                }
                title_line[strlen(title_line) - 1] = '\0';
                leng_title --;
                free((*films + (index))->title);
                (*films + (index))->title = (char*)malloc(sizeof(char) * (strlen(title_line) + 1));
                
                if ((*films + (index))->title == NULL)
                {
                    leng_title = 0;
                    leng_name = 0;
                    free(title_line);
                    free(name_line);	
                    return ERROR;
                }
                strcpy((*films + (index))->title, title_line);
                free((*films + (index))->name);
                (*films + (index))->name = (char*) malloc(sizeof(char) * (strlen(name_line) + 1));
                
                if ((*films + (index))->name == NULL)
                {
                    leng_title = 0;
                    leng_name = 0;
                    free(title_line);
                    free(name_line);	
                    return ERROR;
                }
                strcpy((*films + (index))->name, name_line);
                (*films + (index))->year = year_line;
                
                if ((*films + (index))->year < 0)
                {
                    leng_title = 0;
                    leng_name = 0;
                    free(title_line);
                    free(name_line);	
                    return ERROR;
                }
            }
            else
            {
                index = i - 1;
                
                for (int j = 0; j < i - 1; j ++)
                {
                    if (year_line < (*films + (j))->year)
                    {
                        index = j;
                        break;
                    }
                }
                
                if (move_right(films, index, i))
                {
                    leng_title = 0;
                    leng_name = 0;
                    free(title_line);
                    free(name_line);
                    return ERROR;	
                }			
                title_line[strlen(title_line) - 1] = '\0';
                leng_title --;
                free((*films + (index))->title);
                (*films + (index))->title = (char*) malloc(sizeof(char) * (strlen(title_line) + 1));
                
                if ((*films + (index))->title == NULL)
                {
                    leng_title = 0;
                    leng_name = 0;
                    free(title_line);
                    free(name_line);
                    return ERROR;
                }
                strcpy((*films + (index))->title, title_line);
                free((*films + (index))->name);
                name_line[strlen(name_line) - 1] = '\0';
                leng_name --;
                (*films + (index))->name = (char*)malloc(sizeof(char) * (strlen(name_line) + 1));
                
                if ((*films + (index))->name == NULL)
                {
                    leng_title = 0;
                    leng_name = 0;
                    free(title_line);
                    free(name_line);	
                }
                strcpy((*films + (index))->name, name_line);
                (*films + (index))->year = year_line;
                
                if ((*films + (index))->year < 0)
                {
                    leng_title = 0;
                    leng_name = 0;
                    free(title_line);
                    free(name_line);	
                }
            }
        }
        leng_title = 0;
        leng_name = 0;
        free(title_line);
        free(name_line);
        title_line = NULL;
        name_line = NULL;	
    }
    return OK;
}
void print_films(films_t films[], int len)
{
    for (int i = 0; i < len; i ++)
    {
        printf("%s\n", films[i].title);
        printf("%s\n", films[i].name);
        printf("%d\n", films[i].year);
    }
}
int deep_copy(films_t *to, films_t *from)
{
    char *title_tmp = NULL;
    char *name_tmp = NULL;
    title_tmp = strdup(from->title);
	
    if (title_tmp)
    {
        free(to->title);
        to->title = title_tmp;
    }
    else
    {
        return ERROR;
    }
    name_tmp = strdup(from->name);
	
    if (name_tmp)
    {
        free(to->name);
        to->name = name_tmp;
    }
    else
    {
        return ERROR;
    }
    to->year = from->year;
    return OK;
}
films_t *search_elems(films_t *films, int len, int field, char *key, int *filtered_ind, int *find_flag)
{
    char key_int[5];
    int search_ind;
    films_t *films_filtered = malloc(sizeof(films_t) * len);
	
    for (int i = 0; i < len; i ++)
    {
        (films_filtered + i)->title = NULL;
        (films_filtered + i)->name = NULL;
    }
	
    if (films_filtered == NULL)
    {
        return NULL;
    }

    while (1)
    {
        if (bin_search(films, field, key, &search_ind, len) == ERROR)
        {
            printf("Not found\n"); 
            *find_flag = 1;
            free_struct(&films_filtered, len);   
            return NULL;
        }
        else
        {
            for (int i = search_ind; i >= 0; i --)
            {
                if (i == 0)
                {
                    if (field == 1)
                    {
                        if (strcmp((films + i)->title, key) == 0)
                        {
                            search_ind = i;
                            break;
                        }
                    }
                    else if (field == 2)
                    {
                        if (strcmp((films + i)->name, key) == 0)
                        {
                            search_ind = i;
                            break;
                        }
                    }
                    else if (field == 3)
                    {
                        itoa((films + i)->year, key_int);
                        if (strcmp(key_int, key) == 0)
                        {
                            search_ind = i;
                            break;
                        }
                    }
                }
                
                if (field == 1)
                {
                    if (strcmp((films + i)->title, key))
                    {
                        search_ind = i + 1;
                        break;
                    }
                }
                else if (field == 2)
                {
                    if (strcmp((films + i)->name, key))
                    {
                        search_ind = i + 1;
                        break;
                    }
                }
                else if (field == 3)
                {
                    itoa((films + i)->year, key_int);
                    
                    if (strcmp(key_int, key))
                    {
                        search_ind = i + 1;
                        break;
                    }
                }
            }
            break;
        }
    }
    
    for (int i = search_ind; i < len; i ++)
    {
        if (field == 1)
        {
            if (!strcmp((films + i)->title, key))
            {
                if (deep_copy((films_filtered + *filtered_ind), (films + i)))
                {
                    free_struct(&films_filtered, len);
                    return NULL;
                }
                (*filtered_ind) ++;
            }
        }
        else if (field == 2)
        {
            if (!strcmp((films + i)->name, key))
            {   
                if (deep_copy((films_filtered + *filtered_ind), (films + i)))
                {
                    free_struct(&films_filtered, len);
                    return NULL;
                }
                (*filtered_ind) ++;
            }
        }
        else
        {
            itoa((films + i)->year, key_int);
            
            if (!strcmp(key_int, key))
            {
                if (deep_copy((films_filtered + *filtered_ind), (films + i)))
                {
                    free_struct(&films_filtered, len);
                    return NULL;
                }
                (*filtered_ind) ++;
            }
        }
    }
    return films_filtered;
}
