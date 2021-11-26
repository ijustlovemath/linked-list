#include <stdio.h>
#include "ll.h"

void print_list(const struct singly_linked *root) {
    while(root) {
        printf("%p -> %d\n", root, root->value);
        root = root->next;
    }
    puts("NULL");
}

void init_node(struct singly_linked *new, int value) {
    if(new) {
        new->value = value;
        new->next = NULL;
    }
}

int insert_node(struct singly_linked *root, struct singly_linked *new) {

    /**
     * 1. set new's next to whatever roots next is
     * 2. set root's next to new
     * 3. 1 for success, 0 for failure
     */
    if(root && new) {
        new->next = root->next;
        root->next = new;
        return 1;
    }
    return 0;

}
