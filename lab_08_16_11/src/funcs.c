#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcs.h"
int check_args(int argc, char *argv[], char *in_file1, char *in_file2, char *out_file, int *action)
{
    if (argc != 4 && argc != 5)
    {
        printf("ERROR in argc\n");
        return ERROR;
    }

    if (strcmp(argv[1], "a") == 0)
    {
        if (argc != 5)
            return ERROR;
        *action = SUM;
    }
    else if (strcmp(argv[1], "m") == 0)
    {
        if (argc != 5)
            return ERROR;
        *action = MULT;
    }
    else if (strcmp(argv[1], "o") == 0)
    {
        if (argc != 4)
            return ERROR;
        *action = FIND_DET;
    }
    else
    {
        return ERROR;
    }
    strcpy(in_file1, argv[2]);

    if (argc == 4)
    {
        strcpy(out_file, argv[3]);
    }

    if (argc == 5)
    {
        strcpy(out_file, argv[4]);
        strcpy(in_file2, argv[3]);
    }
    return OK;
}
void free_matr(matr_t matr, int m)
{
    for (int i = 0; i < m; i ++)
    {
        free(matr[i]);
    } 
    free(matr);
}
int create_matrix(matr_t *matr, int m, int n)
{
    matr_t tmp1;
    double *tmp2;
    tmp1 = calloc(m, sizeof(double *));

    if (tmp1 == NULL)
    {
        return ERROR;
    }
    *matr = tmp1;

    for (int i = 0; i < m;  i++)
    {
        tmp2 = malloc(sizeof(double) * n);
        
        if (tmp2 == NULL) 
        {
            free_matr(*matr, m);
            return ERROR;
        }
        *(*matr + i) = (double*)tmp2;
    }
    return OK;
}
int check_input(matr_t *matr, int *m, int *n, char filename[])
{
    FILE *f;
    int input;
    f = fopen(filename, "r");    

    if (!f)
    {
        return ERROR_FILE;
    }
    input = fscanf(f, "%d", m);

    if (input != 1)
    {
        if (fclose(f) == EOF)
            return ERROR;
        return ERROR_INPUT;
    }
    input = fscanf(f, "%d", n);

    if (input != 1)
    {
        if (fclose(f) == EOF)
            return ERROR; 
        return ERROR_INPUT;
    }

    if (!*m || !*n)
    {
        return ERROR_INPUT;
    }

    if (create_matrix(matr, *m, *n))
    {
        return ERROR_MEM;
    }

    for (int i = 0; i < *m; i ++)
    {
        for (int j = 0; j < *n; j ++)
        {
            input = fscanf(f, "%lf", &((*matr)[i][j]));
            
            if (input != 1)
            {
                if (fclose(f) == EOF)
                    return ERROR;
                return ERROR;
            }
        }
    }
    
    if (fclose(f) == EOF)
        return ERROR;
    return OK;
}
void output_matr(matr_t matr, int m, int n)
{
    for (int i = 0; i < m; i ++)
    {
        for (int j = 0; j < n; j ++)
        {
            printf("%lf ", matr[i][j]);
        }
        printf("\n");
    }
}
int f_output_matr(matr_t matr, int m, int n, char filename[])
{
    FILE *f = fopen(filename, "w");

    if (!f)
    {
        return ERROR_FILE;
    }
    fprintf(f, "%d %d\n", m, n);

    for (int i = 0; i < m; i ++)
    {
        for (int j = 0; j < n; j ++)
        {
            fprintf(f, "%lf ", matr[i][j]);
        }
        fprintf(f, "\n");
    }
    
    if (fclose(f) == EOF)
        return ERROR;
    return OK;
}
void copy_str(double *ved_str, matr_t matr, int i, int n)
{
    for (int j = 0; j < n; j ++)
    {
        ved_str[j] = matr[i][j];
    }
}
void mult_on_fig(double *ved_str, int n, double x, int ind)
{
    double mnoj = ved_str[ind];
    for (int i = 0; i < n; i ++)
    {
        ved_str[i] = ved_str[i] * x / mnoj;
    }
}
void vichit_strs(double *ved_str, matr_t matr, int j, int n)
{
    for (int i = 0; i < n; i ++)
    {
        matr[j][i] = matr[j][i] - ved_str[i];
    }
}
int find_det(matr_t matr, int m, int n, char out_file[])
{
    FILE *f;
    double *ved_str;
    double det = 1.0;

    if (m != n)
    {
        return ERROR;
    }
    ved_str = malloc(sizeof(double) * m);

    if (!ved_str)
    {
        return ERROR;
    }

    for (int i = 0; i < n - 1; i ++)
    {
        if (fabs(matr[i][i]) < EPS)
        {
            det = 0.0;
            break;
        }
        
        for (int j = i + 1; j < n; j ++)
        {
            copy_str(ved_str, matr, i, n);
            mult_on_fig(ved_str, n, matr[j][i], i);
            vichit_strs(ved_str, matr, j, n);
            matr[j][i] = 0.0;
        }
    }

    if (!matr[n - 1][n - 1])
        det = 0.0;
    else
    {
        for (int i = 0; i < n; i ++)
        {
            det *= matr[i][i];
        }
    }
    f = fopen(out_file, "w");

    if (!f)
    {
        free(ved_str);
        return ERROR;
    }
    fprintf(f, "%lf", det);

    if (fclose(f) == EOF)
    {
        free(ved_str);
        return ERROR;
    }
    free(ved_str);
    return OK;
}
int sum_matr(matr_t matr1, matr_t matr2, int m1, int n1, int m2, int n2)
{
    if (m1 != m2 || n1 != n2)
    {
        return ERROR;
    }

    for (int i = 0; i < m1; i ++)
    {
        for (int j = 0; j < n1; j ++)
        {
            matr1[i][j] += matr2[i][j];
        }
    }
    return OK;
}
double count_res_elem(matr_t matr1, matr_t matr2, int n1, int i, int j)
{
    double c = 0.0;

    for (int k = 0; k < n1; k ++)
    {
        c = c + (matr1[i][k] * matr2[k][j]);
    }
    return c;
}
int mult_matr(matr_t matr1, matr_t matr2, matr_t *matr_res, int m1, int n1, int m2, int n2)
{
    if (m2 != n1)
    {
        return ERROR_INPUT;
    }

    if (create_matrix(matr_res, m1, n2))
    {
        return ERROR_MEM;
    }

    for (int i = 0; i < m1; i ++)
    {
        for (int j = 0; j < n2; j ++)
        {
            (*matr_res)[i][j] = count_res_elem(matr1, matr2, n1, i, j);
        }
    }
    return OK;
}
int make_sum(char in_file1[], char in_file2[], char out_file[])
{
    matr_t matr;
    matr_t matr2;
    int m1, n1;
    int m2, n2;
    int check;
    check = check_input(&matr, &m1, &n1, in_file1);

    if (check)
    {
        if (check == ERROR)
            free_matr(matr, m1);
        return ERROR;
    }
    check = check_input(&matr2, &m2, &n2, in_file2);

    if (check)
    {
        if (check == ERROR)
        {
            free_matr(matr, m1);
            free_matr(matr2, m2);
        }
        else
        {
            free_matr(matr, m1);
        }
        return ERROR;
    }
    check = sum_matr(matr, matr2, m1, n1, m2, n2);

    if (check)
    {
        if (check == ERROR)
        {
            free_matr(matr, m1);
            free_matr(matr2, m2);
        }	
        return ERROR;
    }
    check = f_output_matr(matr, m1, n2, out_file);

    if (check)
    {
        if (check == ERROR)
        {
            free_matr(matr, m1);
            free_matr(matr2, m2);
        }	
        return ERROR;
    }
    free_matr(matr, m1);
    free_matr(matr2, m2);
    return OK;
}
int make_mult(char in_file1[], char in_file2[], char out_file[])
{
    matr_t matr;
    matr_t matr2;
    matr_t matr_res = NULL;
    int m1, n1;
    int m2, n2;
    int check;
    check = check_input(&matr, &m1, &n1, in_file1);
     
    if (check)
    {
        if (check == ERROR)
            free_matr(matr, m1);
        return ERROR;
    }
    check = check_input(&matr2, &m2, &n2, in_file2);     
  
    if (check)
    {
        if (check == ERROR)
        {
            free_matr(matr, m1);
            free_matr(matr2, m2);
        }
        else
        {
            free_matr(matr, m1);
        }	
        return ERROR;
    }
    check = mult_matr(matr, matr2, &matr_res, m1, n1, m2, n2);    
  
    if (check)
    {
        free_matr(matr, m1);
        free_matr(matr2, m2);			
        return ERROR;
    }
    check = f_output_matr(matr_res, m1, n2, out_file); 

    if (check)
    {
        if (check)
        {
            free_matr(matr, m1);
            free_matr(matr2, m2);
            free_matr(matr_res, m1);
        }		
        return ERROR;
    }
    free_matr(matr, m1);
    free_matr(matr2, m2);
    free_matr(matr_res, m1);
    return OK;
}
int make_find_det(char in_file1[], char out_file[])
{
    matr_t matr;
    int m1, n1;
    int check;
    check = check_input(&matr, &m1, &n1, in_file1);

    if (check)
    {
        if (check == ERROR)
            free_matr(matr, m1);
        return ERROR;
    }

    if (find_det(matr, m1, n1, out_file))
    {
        free_matr(matr, m1);
        return ERROR;			
    }
    free_matr(matr, m1);
    return OK;
}
