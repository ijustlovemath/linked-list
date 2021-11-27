#include <stdio.h>
#include <string.h>

#include "ll.h"

void print_node(const struct singly_linked *root) {
    if(root) {
        printf("%p -> %d\n", root, root->value);
    } else {
        puts("NULL");
    }
}

void print_list(const struct singly_linked *root) {
    while(root) {
        print_node(root);
        root = root->next;
    }
    // We know it's NULL, so save the call to print_node
    puts("NULL");
}

void init_node(struct singly_linked *new, int value) {
    if(new) {
        new->value = value;
        // To test automatic clearing of nodes, comment this out
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

struct singly_linked* create_ordered_list(int total_nodes) {
    static struct singly_linked nodes[100];

    if(total_nodes < 0 || total_nodes > 100) {
        puts("invalid number of nodes requested");
        return NULL;
    }

    // Degenerate but valid case
    if(total_nodes == 0) {
        return NULL;
    }

    // Clear them out; this *automagically* sets all next pointers to NULL!
    memset(nodes, 0, sizeof(nodes));

    for(int i = 0; i < total_nodes; i++) {
        init_node(nodes + i, i);
        if(i) {
            insert_node(nodes + i - 1, nodes + i);
        }
    }
    return nodes;

}

void reverse_list(struct singly_linked **root) {
    /**
     * 1. starting at root:
     *  the * represents our current node
     *  the ^ represents the next node
     *  the p represents the previous node
     *  base case: single element list?
     * initial:
     * a -> b -> c -> d
     * 
     * p    *    ^
     * a -> b -> c -> d
     *
     * p    *    ^
     * 0 <- a <- b    c -> d
     *
     *      p    *    ^
     * a <- b    c -> d
     *
     */
    if(!root || !*root) {
        return;
    }
    struct singly_linked *current=*root, *previous=NULL, *next=(*root)->next;

#if 0
#define DBG_PRINT(name_) printf("%s: ", #name_); print_node(name_);
#else
#define DBG_PRINT(name_)
#endif

    while(next) {
        DBG_PRINT(current)
        DBG_PRINT(previous)
        DBG_PRINT(next)
        // p    *   ^        
        // a <- b   c -> d
        current->next = previous;

        //      p*  ^ 
        // a <- b   c -> d
        previous = current;

        //      p   *^
        // a <- b   c -> d
        current = next;

        //      p   *    ^
        // a <- b   c -> d
        next = next->next;
    };

    // At the very end, we've disconnected the new root from the rest,
    // so connect it back to everything else!
    // TODO: there's probably a way to reorder the steps to remove
    // the need to do this
    current->next = previous;

    *root = current;

}
