#include <stdio.h>
#include <string.h>

#include "ll.h"


/**
 * An aside about if statements and while loops:
 *
 * Several places in this file you'll see pointers
 * used in if statements, like:
 *
 * if(root)
 *
 * OR
 *
 * while(root)
 *
 * This is a shorthand notation in C for
 *
 * if(root != NULL)
 *
 * AND
 *
 * while(root != NULL)
 *
 * The reason why this works is because, in C, pointers
 * can be thought of as numerical addresses. These addresses
 * are always greater than 0, and in C, if(some_number)
 * is the _exact same_ as if(some_number != 0).
 *
 * Addresses are usually large numbers divisible by 8 or 16 or 32 or 64, like 139502496.
 *
 * This is because, for better or worse, 0 is "False" in C,
 * and everything else is "True", even negative numbers like -1.
 */

void print_node(const struct singly_linked *node) {
    if(node) { 
        printf("%p -> %d\n", node, node->value);
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
     * Insert the node "new" right after the node "root".
     * If "root" had a node after it, then "new" will now
     * have that same node after it, and "root" will have
     * "new" after it.
     *
     *
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
    // If we use a static array here, we can
    // return addresses in this array and they will
    // still be valid after this function returns!
    //
    // This is an easy way to use heap based memory,
    // but with the ease-of-use of the stack and no
    // need to worry about memory management
    //
    // This approach does not work when:
    // 1) the code is multi-threaded
    // 2) you need many thousands or millions of nodes
    // in your list. 
    //
    // Because this code is for teaching, and memory
    // management can be a pain, we will use this approach
    // and make our lives easier.
    static struct singly_linked nodes[100];

    if(total_nodes < 0 || total_nodes > 100) {
        puts("invalid number of nodes requested");
        return NULL;
    }

    // Degenerate but valid case; not an error
    if(total_nodes == 0) {
        return NULL;
    }

    // Clear them out; this *automagically* sets all next pointers to NULL!
    // TODO: only clear out nodes we're going to use
    memset(nodes, 0, sizeof(nodes));

    // For each node requested, set its data equal to
    // its own index within our static array.
    //
    // This choice doesn't mean anything, you can also use
    // random numbers if you like, but this is an easier
    // pattern to see if things are working
    for(int i = 0; i < total_nodes; i++) {
        init_node(nodes + i, i);

        // Skip the very first node, which has no predecessor
        // for us to insert it after
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
     * At the beginning, previous is undefined, so use NULL (0)
     * Current (*) is the head of the list, aka a
     * Next (^) is the node following head 
     * p    *    ^
     * 0    a -> b -> c -> d
     *
     * Start by severing the link between a and b,
     * overwriting it by making a point to NULL instead
     *
     * This is okay, because we have ^, which allows us
     * to continue iterating through the list without
     * losing it! This situation is why this approach
     * needs 3 pointers total.
     *
     * The three pointers function like a rolling bridge,
     * allowing us to cross 'gaps' in the data structure
     * without losing access to either side!
     * p    *    ^
     * 0 <- a    b -> c -> d
     *
     *
     * Once we've reassigned the first link,
     * we just move the 'pointer bridge' over by 1,
     * and start over, doing the same thing:
     *
     * Starting arrangement:
     *      p    *    ^
     * 0 <- a    b -> c -> d
     
     * 1. Making the current node point to the previous node
     *      p    *    ^
     * 0 <- a <- b    c -> d
     *
     * 2. Sliding the bridge along!
     *           p    *    ^
     * 0 <- a <- b -> c -> d
     *
     */

    // At the very beginning, we check to see if the
    // root node is itself NULL, in which case our
    // work here is done!
    if(!root || !*root) {
        return;
    }
    struct singly_linked *current=*root, *previous=NULL, *next=current->next;

#if 0
#define DBG_PRINT(name_) printf("%s: ", #name_); print_node(name_);
#else
#define DBG_PRINT(name_)
#endif

    while(next) {
        DBG_PRINT(current)
        DBG_PRINT(previous)
        DBG_PRINT(next)
        // Reassign the link
        // p    *   ^        
        // a <- b   c -> d
        current->next = previous;

        // Slide the previous part of the bridge
        // At this point, both previous and current
        // point to 'b'
        //      p*  ^ 
        // a <- b   c -> d
        previous = current;

        // Slide the current part of the bridge
        // At this point, only previous points to 'b'
        // Both current and next point to 'c'
        //      p   *^
        // a <- b   c -> d
        current = next;

        // Complete the bridge movement by making next
        // point to 'd'.
        //      p   *    ^
        // a <- b   c -> d
        next = next->next;

        // Then we do it all over again!
    };

    // At the very end, we've disconnected the new root from the rest,
    // so connect it back to everything else!
    // TODO: there's probably a way to reorder the steps to remove
    // the need to do this
    // In essence, at the end of the previous loop,
    // the data structure looks like this:
    //                p    *    ^
    // 0 <- a <- b <- c    d -> 0
    //
    // So this last step connects d to c, and
    // reassigns d to be the new head of the list
    current->next = previous;

    *root = current;

}
