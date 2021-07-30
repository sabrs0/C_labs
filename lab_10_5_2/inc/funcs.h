#define OK 0
#define ERROR 1
#define OUT 1
#define CAT 2
#define SPS 3
#define POS 4
typedef struct piece 
{
    char str_p;
    struct piece *next;
}half_dyn_str;
void pop_back(half_dyn_str **head);
int find_node_len(half_dyn_str *node);
half_dyn_str *create_node(char data);
half_dyn_str *add_end(half_dyn_str *head, half_dyn_str *tmp);
void free_list(half_dyn_str *head);
int input_data(int *action, half_dyn_str **head, half_dyn_str **str);
void make_out(half_dyn_str *head);
void make_cat(half_dyn_str *first, half_dyn_str *second, half_dyn_str **res);
void make_sps(half_dyn_str **head);
int get_ind_by_node(half_dyn_str *head, half_dyn_str *cur);
void make_pos(half_dyn_str *head, half_dyn_str *str, int *index);
