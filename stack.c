#include <stdio.h>
#include <stdlib.h>

static const int MAX_STACK_SIZE = 100;

typedef struct stack {
    char **stack;
    int num_elements;
} stack;

stack* new_stack_factory() {
    stack *s = malloc(sizeof(*s));
    s->stack = malloc(sizeof(*(s->stack)) * MAX_STACK_SIZE);
    s->num_elements = 0;
    int i;
    for (i = 0; i < MAX_STACK_SIZE; i++)
        s->stack[i] = 0;
    return s;
}

void free_stack(stack *s) {
    free(s->stack);
    free(s);
}

void print_stack(stack *s) {
    int i;
    for (i = 0; i < s->num_elements; i++)
        printf("%s ", s->stack[i]);
    putchar('\n');
}

int is_empty(stack *s) {
    if (s->num_elements == 0)
        return 1;
    else
        return 0;
}

void push(stack *s, char *new_item){
    if (MAX_STACK_SIZE < s->num_elements)
        printf("Reached stack limit!");
    else
        s->stack[s->num_elements++] = new_item;
}

char* pop(stack *s){
    char* ret;

    if (is_empty(s) == 1) {
        printf("Stack is empty! Can't pop!\n");
        ret = 0;
    } else {
        ret = s->stack[s->num_elements--];
        s->stack[s->num_elements] = 0;
    }
    return ret;
}

int main() {
    stack *st = new_stack_factory();
    push(st, "Hello!");
    push(st, "My");
    push(st, "Name");
    print_stack(st);

    char *popped = pop(st);
    printf("popped = %s\n", popped);
    popped = pop(st);
    popped = pop(st);

    printf("popped = %s\n", popped);
    pop(st);
    pop(st);
    print_stack(st);

    free_stack(st);
}
