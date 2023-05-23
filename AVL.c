#include "AVL.h"

int max(int x, int y)
{
    if(x>y)return x;
    return y;
}

AVL_Node* create_AVL_Node(char *teamName, float points) 
{  
	AVL_Node* newNode = (AVL_Node*)malloc(sizeof(AVL_Node));
    dynamic_allocation_test(newNode);
    newNode->teamName = (char *)malloc((strlen(teamName)+1)*sizeof(char));
    dynamic_allocation_test(newNode->teamName);
    strcpy(newNode->teamName, teamName);
    newNode->points = points;
    newNode->height = 0; //adaugare ca frunza
    newNode->left = newNode->right = NULL;
    return newNode;
}

int AVL_Node_height(AVL_Node *root)
{   
    int hs, hd;
    if(root == NULL)
        return -1;
    hs = AVL_Node_height(root->left);
    hd = AVL_Node_height(root->right);
    return 1 + max(hs,hd); 
}

AVL_Node *rightRotation(AVL_Node *z) 
{   
	AVL_Node *y = z->left;
	AVL_Node *T3 = y->right;	
	y->right = z;
	z->left = T3;
    z->height = 1 + max(AVL_Node_height(z->left), AVL_Node_height(z->right));
    y->height = 1 + max(AVL_Node_height(y->left),AVL_Node_height(y->right));
	return y; 
} 


AVL_Node* AVL_insert(AVL_Node* Node, char *teamName, float points)
{   //daca (sub)arborele e gol, creeaza nod
    if(Node == NULL)
        return create_AVL_Node(teamName,points);
    //altfel, coboara la stanga sau la dreapta
    if(points < Node->points)
        Node->left = AVL_insert(Node->left, teamName, points);
    else 
        if(points > Node->points)   
            Node->right = AVL_insert(Node->right, teamName, points);
    else //puncte egale
        {
            if(strcmp(Node->teamName, teamName)<0)
            Node->right = AVL_insert(Node->right, teamName, points);
            else Node->left = AVL_insert(Node->left, teamName, points);
        }
    Node->height = 1 + max(AVL_Node_height(Node->left), AVL_Node_height(Node->right));
    int k = (AVL_Node_height(Node->left)-AVL_Node_height(Node->right));
    if(k>1)return rightRotation(Node);
    return Node;
}

void print_level(AVL_Node* root, int level,int current_level, FILE *r_out)
{
    if(root == NULL)return;
    else
    {
        if(level == current_level) 
            fprintf(r_out,"%s\n",root->teamName);
        else 
        {
            print_level(root->right, level,current_level+1,r_out);
            print_level(root->left, level, current_level+1,r_out);
        }
    }
}

void level_order_traversal(AVL_Node* root, FILE *r_out)
{   fprintf(r_out,"\n");
    print_level(root, 2,0, r_out); //afisam nodurile de pe nivelul 2
}

void delete_AVL_Tree(AVL_Node* root) 
{
    if (root == NULL) 
        return;
        
    delete_AVL_Tree(root->left);
    delete_AVL_Tree(root->right);

    free(root->teamName);
    free(root);
}