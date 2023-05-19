#include "team.h"
#include "stive.h"
#include "cozi.h"
int isEmpty_stack(Stack* top)
{
	return top==NULL;
}

Team* top_stack(Stack* top)
{
	if (isEmpty_stack(top)) return NULL;
	return top->team;
} 

void push(Stack*** top, Team* team)
{
	Stack* newNode=(Stack*)malloc(sizeof(Stack));
	newNode->team=team;
	newNode->next=**top;
	**top=newNode;
}

Team* pop(Stack** top) 
{
	if (isEmpty_stack(*top)) return NULL;
	Stack *temp=(*top); 		
	Team* aux=temp->team;	
	*top=(*top)->next;      		
	free(temp);
	return aux;
}

void deleteStack(Stack** top)
{	if(isEmpty_stack)return;
	Stack  *temp;
	while (!isEmpty_stack(*top))
		temp=*top;
		*top=(*top)->next;
		free(temp);
}

void create_stacks(Queue *q, Stack **winners_stack, Stack** loosers_stack) //atentie ca goleste coada
{	*winners_stack = NULL;
	*loosers_stack = NULL;
	while(!isEmpty_Q(q))
	{
		Team *team1 =(Team *)malloc(sizeof(Team));
		Team *team2=(Team *)malloc(sizeof(Team));
		deQueue(q,&team2,&team1);
		if(team1->team_points >= team2->team_points)
		{	team1->team_points++;
			push(&winners_stack,team1);
			push(&loosers_stack,team2);
		}	
		else
		{	team2->team_points++;
			push(&winners_stack,team2);
			push(&loosers_stack,team1);
		}	
	}
}

void print_Stack(Stack* top, FILE *r_out)
{	int ok = 0; //ok pentru a nu afisa 2 endline-uri la final de tot
	if(isEmpty_stack(top))
	{
		fprintf(r_out,"%s","Stiva e goala :(\n");
		return;
	}
	if(top->next==NULL) ok = 1;
	//nr_spatii = 34 - lungime(sir)
	while(!isEmpty_stack(top))
	{
		Team *t = pop(&top);
		fprintf(r_out, "%s", t->team_name);
		for(int i=1; i<=34-strlen(t->team_name); i++)
			fprintf(r_out, "%c", ' ');
		fprintf(r_out, "%c  %.2f\n", '-',t->team_points);
	}
	if(!ok) 
		fprintf(r_out, "%c", '\n'); //atentie ca pe asta nu trb sa-l mai faci la final de tot
}

void create_winners_match_queue(Queue *q, Stack *head_team) //asta poti sa o generalizezi pt ca e aceeasi cu create_match_queue()
{   Stack* prev = head_team, *current = head_team->next;
    while (current!=NULL)
    {
        enQueue(q,prev->team, current->team);
		if(current->next==NULL)return;
        prev=current->next;
        current=prev->next;
    }
}