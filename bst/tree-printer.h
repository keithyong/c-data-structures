typedef struct tree {
    int data;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} tree;

int _print_t(tree *t, int is_left, int offset, int depth, char s[20][255]);
int print_t(tree *t);
