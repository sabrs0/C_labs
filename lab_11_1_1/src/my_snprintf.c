#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include "../inc/funcs.h"
int put_char(size_t *buf_ind, size_t size, char *buf, char c)
{
    if (*buf_ind < size && buf)
    {
        buf[*buf_ind] = c;
    }

    (*buf_ind) ++;
    return 0;
}
int itoa(int fig, char **s)
{
    int fig_copy = fig;
    int s_len = 0;
    int i = 0;
    int flag = 1;
    if (!fig)
    {
        **s = '0';
        return 1;
    }
    while (fig_copy)
    {
        fig_copy /= 10;
        s_len ++;
    }
    int numb;
    if (fig < 0)
        flag = -1;
    for (int j = s_len - 1; j >= 0; j --)
    {
        numb = fig % 10 * flag;
        *(*s + j) = numb + 48;
        fig /= 10;
    }
    return s_len * flag;
}
int put_int(size_t *buf_ind, size_t size, char *buf, int d)
{
    char *str;
    str = malloc(sizeof(char) * MAX_FIG_LEN);
    
    if (!str)
        return -1;
    
    int len_s = itoa(d, &str);
    
    if (len_s < 0)
    {
        if (*buf_ind < size && buf)
        {
            buf[*buf_ind] = '-';
        }
        
        (*buf_ind) ++;
        len_s *= -1;
    }
    
    for (int i = 0; i < len_s; i ++)
    {   
        if (*buf_ind < size && buf)
        {
            buf[*buf_ind] = str[i];
        }
        
        (*buf_ind) ++;
    }
    
    free(str);
    return 0;
}
int my_strlen(char *str)
{
    int i;
    
    for (i = 0; str[i] != '\0'; i ++);
    
    return i;
}
int put_str(size_t *buf_ind, size_t size, char *buf, char *s)
{
    int len_s = my_strlen(s);
    
    for (int i = 0; i < len_s; i ++)
    {   
        if (*buf_ind < size && buf)
        {
            buf[*buf_ind] = s[i];
        }
        
        (*buf_ind) ++;
    }
    
    return 0;
}
int my_snprintf(char *buf, size_t size, char *format, ...)
{
    va_list v;
    int d;
    char c;
    char *s;
    double f;
    long ld;
    int format_ind = 0;
    size_t buf_ind = 0;
    int len_f = my_strlen(format);
    
    if (size > INT_MAX)
        return -1;
    
    if (*(format + format_ind) == '\0')
    {   
        if (size && buf)
        {
            buf = '\0';
        }
        
        return 0;
    }
    va_start(v, format);
    
    while (format_ind < len_f)
    {   
        if (*(format + format_ind) == '%')
        {  
            if (format_ind + 1 < len_f)
            {       
                if (*(format + format_ind + 1) == 'd')
                {
                    d = va_arg(v, int);
                    put_int(&buf_ind, size, buf, d);
                    format_ind ++;
                }
                else if (*(format + format_ind + 1) == 'i')
                {
                    d = va_arg(v, int);
                    put_int(&buf_ind, size, buf, d);
                    format_ind ++;
                }
                else if (*(format + format_ind + 1) == 'c')
                {
                    c = (char) va_arg(v, int);
                    put_char(&buf_ind, size, buf, c);
                    format_ind ++;
                }
                else if (*(format + format_ind + 1) == 's')
                {
                    s = va_arg(v, char *);
                    put_str(&buf_ind, size, buf, s);
                    format_ind ++;
                }
                else if (*(format + format_ind + 1) == '%')
                {
                    put_char(&buf_ind, size, buf, '%');
                    format_ind ++;
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            put_char(&buf_ind, size, buf, *(format + format_ind));
        }
        
        format_ind ++;
    }
    
    if (size)
    {
        if (buf_ind < size)
            *(buf + buf_ind) = '\0';
        else
            *(buf + size - 1) = '\0';
    }
    
    va_end(v);
    return buf_ind;
}
