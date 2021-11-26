#include "ll.h"
#include <stddef.h>
#include <stdio.h>

void test1 (void) {
    static struct singly_linked nodes[20];
    struct singly_linked *root = nodes;

    for(int i = 0; i < sizeof(nodes)/sizeof(*nodes); i++) {
        init_node(nodes + i, i);
        if(i) {
            insert_node(nodes + i - 1, nodes + i);
        }
    }
    print_list(root);
}

int main(void) {
    test1();
    struct singly_linked *root = NULL, first;
    init_node(&first, 1);
    root = &first;
    print_list(root);
    puts("printed first");
    NODE(root, 2);
    print_list(root);
    return 0;
}
