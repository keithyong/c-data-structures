#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char* str;
    struct node *next;
} node;

/* --- parse_linked_list -----------------------------------------
 * Given a string array, makes a linked list structure based off 
 * of that string array and return the head of the linked list. */
node* parse_linked_list(char ** str_arr) {
    if (str_arr == NULL) {
        return NULL;
    }

    /* Initiate starting nodes */
    node *head;
    node **constructor = &head;

    /* Traverse through str array */
    while (*str_arr) {
        /* Malloc a new node data structure under constructor */
        *constructor = malloc(sizeof(**constructor));

        /* Set constructor's string */
        (*constructor)->str = *str_arr;

        /* Move constructor to the next node */
        constructor = &((*constructor)->next);
        
        /* Move str arr ptr to next */
        str_arr++;
    }

    /* NULL terminate the linked list. */
    *constructor = NULL;
    return head;

    /* The biggest source of segfaults in linked list is
     * doing NULL->next. That is the current node is NULL
     * and you're trying to access NULL's next which is
     * not good. */
}

/* --- parse_linked_list -----------------------------------------
 * Go through the list and print out the linked list. */
void traverse_linked_list(node *head) {
    if (head == NULL) {
        printf("(null head)\n");
    } else {
        for (; head->next; head = head->next)
            printf("%s -> ", head->str);
        printf("%s", head->str);
        putchar('\n');
    }
}

/* --- push_front ------------------------------------------------
 * Insert in the front of a linked list, or the beginning */
void push_front(node **head, char *new_node_str) {
    node *new_node = malloc(sizeof(*new_node));
    new_node->str = new_node_str;
    new_node->next = *head;
    *head = new_node;
}

/* --- push_back -------------------------------------------------
 * Insert in the back of a linked list, or the end */
void push_back(node *head, char *new_node_str) {
    /* Move head pointer to last node */
    while (head->next) {
        head = head->next;
    }
    
    node *new_node = malloc(sizeof(*new_node));
    new_node->str = new_node_str;
    new_node->next = NULL;
    head->next = new_node;
}

/* --- search ----------------------------------------------------
 * Given a head node, searches for string match in linked list and
 * return the node of that match. Return NULL if not found. */
node* search(node *head, char *search_str) {
    while (head) {
        if (!strcmp(head->str, search_str))
            return head;
        head = head->next;
    }

    return NULL;
}

/* --- delete ----------------------------------------------------
 * Given a head node and a string match, find and delete the first 
 * node of the string match. */
int delete(node **head, char *delete_str) {
    node *prev = NULL;
    node *tmp;

    while (*head) {
        if (!strcmp((*head)->str, delete_str)) {
            /* If head is the one we want to delete... */
            tmp = *head;
            if ((*head)->next == NULL) {
                *head = NULL;
                free(tmp);
                return 0;
            } else if (prev == NULL) {
                *head = (*head)->next;
                free(tmp);
                return 1;
            } else {
                prev->next = (*head)->next;
                free(tmp);
                return 1;
            }
        }
        prev = (*head);
        head = &((*head)->next);
    }

    return 0;
}

/* --- main ------------------------------------------------------ */
int main(int argc, char *argv[]) {
    char **argv_cpy = argv;
    /* Ignore ./a.out in argv_cpy */
    argv_cpy++;
    
    node *head = parse_linked_list(argv_cpy);
    traverse_linked_list(head);
    push_back(head, "Hello");
    traverse_linked_list(head);
    node *search_ans = search(head, "Hello");
    printf("search_ans->str = %s\n", search_ans->str);
    delete(&head, argv[1]);
    delete(&head, argv[2]);
    delete(&head, argv[3]);
    delete(&head, "Hello");
    traverse_linked_list(head);
}
