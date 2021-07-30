#ifndef FILE_MAX_SIZE
#define FILE_MAX_SIZE 256
#define ERROR 1
#define OK 0
#define ERR_INVALID_PTR -1
#endif
int comparator(const void *x1, const void *x2);
void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *));
int key(int *pb_src, int *pe_src, int **pb_dst, int **pe_dst);
int checking_args(int argc, char *argv[], char *in_file, char *out_file);
int checking_data(char in_file[], int *n);
int create_array(int n, int **arr_tail, int **arr_head);
int init_array(char in_file[], int *arr_tail);
int output_array(char out_file[], int *arr_new_tail, int *arr_new_head);
