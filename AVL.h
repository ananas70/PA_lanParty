#ifndef AVL_H
#define AVL_H

#include "team.h"
#include "stive.h"
#include "files.h"
struct avl_node
{
    int height;
    char *teamName;
    float points;
    struct avl_node *left, *right;
};

typedef struct avl_node AVL_Node;

int max(int x, int y);
AVL_Node* create_AVL_Node(char *teamName, float points);
int AVL_Node_height(AVL_Node *root);
AVL_Node* rightRotation(AVL_Node *z); 
AVL_Node* AVL_insert(AVL_Node* Node, char *teamName, float points);
void print_level(AVL_Node* root,int level, int current_level, FILE *r_out);
void level_order_traversal(AVL_Node* root, FILE *r_out);
void delete_AVL_Tree(AVL_Node* root);


#endif //AVL_H