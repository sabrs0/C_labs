#ifndef MAX_FIG_LEN
#define MAX_FIG_LEN 25
#define OK 0
#define ERROR 1
#endif
int put_char(size_t *buf_ind, size_t size, char *buf, char c);
int itoa(int fig, char **s);
int put_int(size_t *buf_ind, size_t size, char *buf, int d);
int my_strlen(char *str);
int put_str(size_t *buf_ind, size_t size, char *buf, char *s);
int my_snprintf(char *buf, size_t size, char *format, ...);
