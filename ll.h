#pragma once

#define ADD_NODE_STATIC(root_, value_, node_name_)\
    init_node(&(node_name_), (value_)); \
    if(insert_node((root_), &(node_name_))) { \
        puts(#node_name_ " inserted successfully");\
    } else {\
        puts(#node_name_ " failed to insert");\
    }



#define AUTO_NODE(root_, value_, line_) \
    struct singly_linked node ## line_;\
    ADD_NODE_STATIC((root_), (value_), node ## line_)

#define NODE(root_, value_) AUTO_NODE(root_, value_, __LINE__)

struct singly_linked {
    int value;
    struct singly_linked *next;
};

int insert_node(struct singly_linked *, struct singly_linked *);
void init_node(struct singly_linked *new, int value);
void print_list(const struct singly_linked *root);
