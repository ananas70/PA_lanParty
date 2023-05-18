#include "team.h"
#include "stive.h"

int isEmpty_stack(Node* top)
{
	return top==NULL;
}

Team* top(Node* top)
{
	if (isEmpty_stack(top)) return NULL;
	return top->team;
} 

void push(Node** top, Team* team)
{
	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->team=team;
	newNode->next=*top;
	*top=newNode;
}

Team* pop(Node** top) 
{
	if (isEmpty_stack(*top)) return NULL;
	Node *temp=(*top); 		
	Team* aux=temp->team;	
	*top=(*top)->next;      		
	free(temp);
	return aux;
}

void deleteStack(Node** top)
{
	Node  *temp;
	while (!isEmpty_stack(*top))
		temp=*top;
		*top=(*top)->next;
		free(temp);
	}
