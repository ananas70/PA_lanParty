#include "BST.h"

void init_tree(Node **root)
{
    (*root) = (Node*)malloc (sizeof(Node));
    (*root)->left=(*root)->right=NULL;
}

Node* createNode(char *teamName, float points) 
{   
    Node* newNode = (Node*)malloc(sizeof(Node));
    dynamic_allocation_test(newNode);
    newNode->teamName = (char *)malloc((strlen(teamName)+1)*sizeof(char));
    dynamic_allocation_test(newNode->teamName);
    strcpy(newNode->teamName, teamName);
    newNode->points = points;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* node, char *teamName, float points)
{   //daca (sub)arborele e gol, creeaza nod
    if(node == NULL) 
        return createNode(teamName,points);
    //altfel, coboara la stanga sau la dreapta
    if(points < node->points)
        node->left = insert(node->left, teamName, points);
    else 
        if(points > node->points)   
            node->right = insert(node->right, teamName, points);
    else //puncte egale
        {
            if(strcmp(node->teamName, teamName)<0)
            node->right = insert(node->right, teamName, points);
            else node->left = insert(node->left, teamName, points);
        }
    return node;    //pointerul se intoarce nemodificat pe acest return
}

void DRS (Node* root, FILE* r_out, AVL_Node **avl_root)
{
    if(root)
    {
        DRS(root->right, r_out, avl_root);
        fprintf(r_out, "%s",root->teamName);
        (*avl_root) = AVL_insert(*avl_root,root->teamName,root->points);
        for(int i=1; i<=34-strlen(root->teamName); i++)
			fprintf(r_out, "%c", ' ');
		fprintf(r_out, "%c  %.2f\n", '-',root->points);
        DRS(root->left,r_out, avl_root);
    }
}

Node* create_last_8_BST_tree(Stack *winners_stack)
{   if(isEmpty_stack(winners_stack))
    {
        printf("stiva winner e goala\n");
        return NULL;
    }
    Node* root = createNode(winners_stack->team->team_name, winners_stack->team->team_points);
    winners_stack=winners_stack->next;
    while(!isEmpty_stack(winners_stack))
    {
    Team* aux = winners_stack->team;
    root = insert(root, aux->team_name, aux->team_points);
    winners_stack=winners_stack->next;
    }
    return root;
}