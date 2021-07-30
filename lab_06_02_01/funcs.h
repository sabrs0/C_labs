#define PREFIX_SIZE 26
typedef struct
{
    char name[PREFIX_SIZE];
    double mass;
    double value;
    double density;
} item_info;
void print_array_by_prefix(item_info item_arr[], int n, char prefix[]);
void print_array(item_info item_arr[], int n);
void fill_array(item_info item_arr[], FILE *f);
int create_array(item_info **arr, int n);
int check_input(FILE *f, item_info item, int *n, char filename[]);
int comparator(const void *x1, const void *x2);
int checking_arguments(int argc, char *argv[], char *filename, char *prefix);
