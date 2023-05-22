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
    // newNode->height = 0; //adaugare ca frunza
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
    return 1 + ((hs > hd) ? hs:hd); 
}

AVL_Node *rightRotation(AVL_Node *z) 
{   
    //test
    if(z==NULL || z->left ==NULL){printf("ups\n");return z;}
    //test
	AVL_Node *y = z->left;
	AVL_Node *T3 = y->right;	
    if(y->right == NULL){printf("ups\n");return z;}
	y->right = z;
	z->left = T3;
    z->height = 1 + max(AVL_Node_height(z->left), AVL_Node_height(z->right));
    y->height = 1 + max(AVL_Node_height(y->left),AVL_Node_height(y->right));
	return y; 
} 

AVL_Node* leftRotation(AVL_Node* z) 
{
	AVL_Node *y = z->right;
    if(y==NULL && z->right == NULL){printf("ups\n");return z; }
	AVL_Node *T2 = y->left;
	y->left = z;
    if(y->left == NULL){printf("ups\n");return z;}
	z->right = T2;
    z->height =1 + max(AVL_Node_height(z->left), AVL_Node_height(z->right));
    y->height =1 + max(AVL_Node_height(y->left),AVL_Node_height(y->right));
	return y;
}

AVL_Node* LRRotation(AVL_Node* Z) 
{
    if (Z == NULL || Z->left == NULL || Z->left->right == NULL)
        return Z;
	Z->left = leftRotation(Z->left);
	return rightRotation(Z);
}

AVL_Node* RLRotation(AVL_Node*Z) 
{ 
     if (Z == NULL || Z->right == NULL || Z->right->left == NULL)
        return Z;
	Z->right = rightRotation(Z->right);
	return leftRotation(Z);
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
    if(k > 1 && ((points < Node->left->points) || (points == Node->left->points && strcmp(teamName, Node->left->teamName)>0)))
        return rightRotation(Node);
    if(k < -1 && ((points > Node->right->points) || (points == Node->right->points && strcmp(teamName, Node->right->teamName)<0)))
        return leftRotation(Node);
    if(k > 1 && ((points > Node->left->points) || (points == Node->left->points && strcmp(teamName, Node->left->teamName)<0)))
        return RLRotation(Node);
    if(k < -1 && ((points < Node->right->points) || (points == Node->right->points && strcmp(teamName, Node->right->teamName)>0)))
        return LRRotation(Node);
    printf("root = %s\n", Node->teamName);
    return Node;
}

void print_level(AVL_Node* root, int level, FILE *r_out)
{
    if(root == NULL) return;
    if(level == 0) fprintf(r_out,"%s\n",root->teamName);
    else
        if(level >= 1)
        {
            print_level(root->left, level-1,r_out);
            print_level(root->right, level-1,r_out);
        }
}

void level_order_traversal(AVL_Node* root, FILE *r_out)
{    int h = AVL_Node_height(root);
    printf("inaltimme  (%s) = %d\n",root->teamName, h);
     fprintf(r_out,"\n");
    // for(int i=0;i<=h;i++)
        print_level(root, 3, r_out);
    
}

AVL_Node* create_last_8_AVL_tree(Stack* winners_stack)
{
    if(isEmpty_stack(winners_stack))
    {
        printf("stiva winner e goala\n");
        return NULL;
    }
    AVL_Node *root = create_AVL_Node(winners_stack->team->team_name, winners_stack->team->team_points);
    printf("root = %s\n",root->teamName);
    winners_stack=winners_stack->next;
    while(!isEmpty_stack(winners_stack))
    {
        printf("bagam din stiva : %s\n",winners_stack->team->team_name);
    Team* aux = winners_stack->team;
    root = AVL_insert(root, aux->team_name, aux->team_points);
    winners_stack=winners_stack->next;
    }
    return root;
}
