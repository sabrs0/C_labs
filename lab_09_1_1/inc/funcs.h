#define OK 0
#define ERROR 1
#define MAX_FILE_NAME 256

typedef struct
{
    char *title;
    char *name;
    int year;
}films_t;
int count_len(int *len, FILE *f);
void free_struct(films_t **films, int len);
int powering(int a, int power);
void itoa(int numb, char *string);
int check_args(int argc, char **argv, char in_file[], int *field, char **key);
int move_right(films_t **films, int index, int len);
int bin_search(films_t *films, int field, char *key, int *search_ind, int len);
int scan_films(FILE *f, films_t **films, int field, int /* * */len);
void print_films(films_t films[], int len);
films_t *search_elems(films_t *films, int len, int field, char *key, int *filtered_ind, int *find_flag);
int deep_copy(films_t *to, films_t *from);

