#define FILE_MAX_SIZE 256
#define ERROR 1
#define OK 0
#define ERROR_2 2
typedef struct node node_t;
struct node
{
    void *data;
    node_t *next;
};
void free_list(node_t *head);
int print_list(node_t *head);
node_t *init_list(node_t *head, char filename[]);
int comparator(const void *v1, const void *v2);
int copy_mem_str(void **from, void *to);
int check_args(int argc, char **argv, int *action, char filename[], void **key);
int find_node_len(node_t *node);
node_t *create_node(char *data);
node_t *add_end(node_t *head, node_t *tmp);
void front_back_split(node_t *head, node_t **back);
node_t *insert_node(node_t **head, void *elem, int (*comparator)(const void *x1, const void *x2));
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *x1, const void *x2));
node_t *reverse(node_t *head);
node_t *sort(node_t *head, int (*comparator)(const void *x1, const void *x2));
node_t *find(node_t *head, void *data, int (*comparator)(const void *x1, const void *x2));
void *pop_front(node_t **head);
