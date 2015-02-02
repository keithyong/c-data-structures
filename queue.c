#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char *str;
    struct node *next;
} node;

typedef struct queue {
    node *head;
    node *tail;
} queue;

void print_queue(queue *q) {
    node *curr = q->head;
    for (; curr; curr = curr->next) {
        printf("%s ", curr->str);
    }
    putchar('\n');
}

void enqueue(queue *q, char* new_str) {
    /* Create new node */
    node *new_node = malloc(sizeof(*new_node));
    new_node->str = new_str;

    /* Append new node to beginning of LL */
    new_node->next = q->head;
    q->head = new_node;
}

node* dequeue(queue *q) {
    node *dequeued_node = q->tail;
    node *curr = q->head;
    node *prev;

    /* Move curr to tail so we can find tail->prev */
    for (; curr->next; curr = curr->next)
        prev = curr;

    free(curr);
    prev->next = NULL;
    q->tail = prev;
}

int main() {
    queue *my_q = malloc(sizeof(*my_q));
    enqueue(my_q, "a");
    enqueue(my_q, "b");
    enqueue(my_q, "c");
    print_queue(my_q);
    dequeue(my_q);
    dequeue(my_q);
    print_queue(my_q);
    enqueue(my_q, "d");
    enqueue(my_q, "e");
    enqueue(my_q, "f");
    dequeue(my_q);
    print_queue(my_q);
}
