#include <stdio.h>
#include "ll.h"

void print_list(const struct singly_linked *root) {
    while(root) {
        printf("%p -> %d\n", root, root->value);
        root = root->next;
    }
    puts("NULL");
}
