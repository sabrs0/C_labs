#define ERROR_FILE 2
#define ERROR_INPUT 3
#define ERROR_MEM 4
#define ERROR 1
#define OK 0
#define EPS 0.00000001
#define ERR_INVALID_PTR -1
#define SUM 1
#define MULT 2
#define FIND_DET 3
typedef double **matr_t;
int check_args(int argc, char *argv[], char *in_file1, char *in_file2, char *out_file, int *action);
void free_matr(matr_t matr, int m);
int create_matrix(matr_t *matr, int m, int n);
int check_input(matr_t *matr, int *m, int *n, char filename[]);
void output_matr(matr_t matr, int m, int n);
int f_output_matr(matr_t matr, int m, int n, char filename[]);
void copy_str(double *ved_str, matr_t matr, int i, int n);
void mult_on_fig(double *ved_str, int n, double x, int ind);
void vichit_strs(double *ved_str, matr_t matr, int j, int n);
int find_det(matr_t matr, int m, int n, char out_file[]);
int sum_matr(matr_t matr1, matr_t matr2, int m1, int n1, int m2, int n2);
double count_res_elem(matr_t matr1, matr_t matr2, int n1, int i, int j);
int mult_matr(matr_t matr1, matr_t matr2, matr_t *matr_res, int m1, int n1, int m2, int n2);
int make_sum(char in_file1[], char in_file2[], char out_file[]);
int make_mult(char in_file1[], char in_file2[], char out_file[]);
int make_find_det(char in_file1[], char out_file[]);
