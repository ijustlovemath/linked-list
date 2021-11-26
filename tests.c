#include "ll.h"
#include <stddef.h>
#include <stdio.h>


void test1 (void) {
    struct singly_linked *root = create_ordered_list(20);

    print_list(root);
}

void test2(void) {
    struct singly_linked *root = NULL, first;
    init_node(&first, 1);
    root = &first;
    print_list(root);
    puts("printed first");
    NODE(root, 2);
    print_list(root);
}

void test_reverse(int total_nodes) {
    printf("## List reversal test: %d nodes ##\n", total_nodes);
    struct singly_linked *root = create_ordered_list(total_nodes); 

    puts("-- INITIAL LIST --");
    print_list(root);

    reverse_list(&root);

    puts("-- FINAL LIST --");
    print_list(root);
}

int main(void) {
    create_ordered_list(-1);
    create_ordered_list(200);
    test1();
    test_reverse(5);
    test_reverse(1);
    test_reverse(0);
    return 0;
}
