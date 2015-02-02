#include <stdio.h>
#include <stdlib.h>
#include "tree-printer.h"

/* Malloc a new tree node and return the pointer to it. */
tree *tree_factory(int tree_data) {
    tree *new_tree = malloc(sizeof(*new_tree));
    new_tree->data = tree_data;
    new_tree->left = NULL;
    new_tree->right = NULL;
    new_tree->parent = NULL;

    return new_tree;
}

/* Search for a tree node and return it
 * if found. O(height) */
tree *search_tree(tree *t, int query) {
    if (t == NULL) return NULL;
    if (t->data == query) return t;
    if (t->data < query)
        return search_tree(t->right, query);
    else
        return search_tree(t->left, query);
}

/* Find minimum value of tree and
 * return the containing node. O(height) */
tree *find_min(tree *t) {
    tree *min;
    if (t == NULL) return NULL;
    min = t;
    /* Keep going to the left most subtree - this
     * will give us the min. */
    while (min->left != NULL)
        min = min->left;
    return min;
}

/* Find maximum value of tree and
 * return the containing node. O(height) */
tree *find_max(tree *t) {
    tree *max;
    if (t == NULL) return NULL;
    max = t;
    /* Keep going to the left most subtree - this
     * will give us the min. */
    while (max->right != NULL)
        max = max->right;
    return max;
}

/* Go through each tree node and print
 * its data. O(n). */
void traverse_tree(tree *t) {
    /* AKA inorder traversal */
    if (t != NULL) {
        traverse_tree(t->left);
        printf("%d ", t->data);
        traverse_tree(t->right);
    }
}

/* Free the tree from memory O(n)*/
void free_tree(tree **t) {
    /* AKA inorder traversal */
    if (*t != NULL) {
        free_tree(&((*t)->left));
        free(*t);
        free_tree(&((*t)->right));
    }
}

/* Insert a data into a BST. O(h) */
int insert_tree(tree **root, tree *parent, int new_node_data) {
    /* If we hit the end of our search, this is where we 
     * replace the current NULL node with a new node */
    if (*root == NULL) {
        tree *new_node = tree_factory(new_node_data);
        new_node->parent = parent;
        *root = new_node;
        return 1;
    }

    /* If node data is less than curr node data, 
     * move left. Otherwise move right. */
    if (new_node_data < (*root)->data) {
        insert_tree(&((*root)->left), *root, new_node_data);
    } else {
        insert_tree(&((*root)->right), *root, new_node_data);
    }

}

int delete_tree(tree **root, int target_num) {
    /* Traverse through the tree looking for the node
     * to delete. */
    if ((*root)->data == target_num) {
        /* If node to delete has no children... */
        if (((*root)->left == NULL) && ((*root)->right == NULL)) {
            free(*root);
            (*root) == NULL;
            return 1;
        }
        /* If left child but not right child */
        else if (((*root)->left != NULL) && ((*root)->right == NULL)) {
            (*root)->left->parent = (*root)->parent;
            (*root)->parent->left = (*root)->left;
            free(*root);
            return 1;
        }
        /* If right child but not left child */
        else if (((*root)->left == NULL) && ((*root)->right != NULL)) {
            (*root)->right->parent = (*root)->parent;
            (*root)->parent->right = (*root)->right;
            free(*root);
            return 1;
        } else {
            /* Replace node to delete's value with the min of right subtree's
             * value, then delete the min of right subtree node. */
            tree *min_of_right_subtree = find_min((*root)->right);
            (*root)->data = min_of_right_subtree->data;
            delete_tree(&min_of_right_subtree, min_of_right_subtree->data);
        }
    }
    else if ((*root)->data < target_num) {
        delete_tree(&((*root)->right), target_num);
    } else {
        delete_tree(&((*root)->left), target_num);
    }

    /* We can't find the node to delete so just do nothing. */
    return 0;
}

int main() {
    tree *root = tree_factory(7);

    insert_tree(&root, root->parent, 4);
    insert_tree(&root, root->parent, 5);
    insert_tree(&root, root->parent, 6);
    insert_tree(&root, root->parent, 9);
    insert_tree(&root, root->parent, 10);
    insert_tree(&root, root->parent, 2);
    insert_tree(&root, root->parent, 1);


    tree *min_val = find_min(root);
    tree *max_val = find_max(root);


    printf("min_val = %d\n", min_val->data);
    printf("max_val = %d\n", max_val->data);
    print_t(root);

    insert_tree(&root, root->parent, 199);
    insert_tree(&root, root->parent, 22);
    print_t(root);

    delete_tree(&root, 7);
    delete_tree(&root, 9);
    delete_tree(&root, 4);
    print_t(root);
    free_tree(&root);
}
