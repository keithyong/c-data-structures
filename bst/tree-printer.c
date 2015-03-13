/* stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console */
#include "tree-printer.h"
#include <stdio.h>

int _print_t(tree *t, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;

    if (!t) return 0;

    sprintf(b, "(%03d)", t->data);

    int left  = _print_t(t->left,  1, offset,                depth + 1, s);
    int right = _print_t(t->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        int i;
        for (i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        int i;
        for (i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else 
    int i;
    for (i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        int i;
        for (i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        int i;
        for (i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

int print_t(tree *t)
{
    char s[20][255];
    int i;
    for (i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(t, 0, 0, 0, s);

    for (i = 0; i < 20; i++)
        printf("%s\n", s[i]);

    return 0;
}
