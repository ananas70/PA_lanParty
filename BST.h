#ifndef TREE_H
#define TREE_H

#include "AVL.h"
#include "team.h"
#include "stive.h"
#include "files.h"
struct node 
{
    char *teamName;
    float points;
    struct node *left, *right;
};
typedef struct node Node;

void init_tree(Node **root);
Node* createNode(char *teamName, float points); 
Node* insert(Node* node, char *teamName, float points);
void DRS (Node* root, FILE* r_out, AVL_Node **avl_root);
Node* create_last_8_BST_tree(Stack *winners_stack);
void delete_BST_Tree(Node* root);
#endif // TREE_H