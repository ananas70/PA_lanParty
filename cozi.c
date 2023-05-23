#include "team.h"
#include "stive.h"
#include "cozi.h"

int isEmpty_Q(Queue*q)
{
	return (q->front==NULL);
}

Queue* create_empty_Queue()
{
	Queue *q;
	q=(Queue *)malloc(sizeof(Queue));
	if (q==NULL) 
        return NULL;	
	q->front = q->rear=NULL;
	return q;	
}

void enQueue(Queue* q, Team* t1, Team* t2)
{
	Meci* newMatch = (Meci*)malloc(sizeof(Meci));
	newMatch->team1 = t1;
    newMatch->team2 = t2;
	newMatch->next = NULL;
	if (q->rear==NULL) 
        q->rear = newMatch; 
	else
    {
		(q->rear)->next = newMatch;
		(q->rear) = newMatch;
	}
	if (q->front==NULL) 
        q->front = q->rear; 
}
 
void deQueue(Queue* q, Team **team1, Team **team2)  //returneaza meciurile prin referinta
{  
	Meci* aux;
	if (isEmpty_Q(q)) 
	{
		*team1 = NULL;
    	*team2 = NULL;
		return;
	}
	aux = q->front; 
	(*team1) = aux->team1;
    (*team2) = aux->team2;
	q->front = (q->front)->next;
	free(aux);
} 

void deleteQueue(Queue* q)
{
	Meci* aux;
	while (!isEmpty_Q(q))
    {
		aux = q->front;
		q->front = q->front->next;
		free(aux);
	}
	free(q);
}	

void create_match_queue(Queue *q, Team *head_team)
{   Team* prev = head_team, *current = head_team->team_next;
    while (current!=NULL)
    {
        enQueue(q,prev, current);
		if(current->team_next==NULL)return;
        prev=current->team_next;
        current=prev->team_next;
    }
}

void print_queue(Queue *q, FILE* r_out)
{  	Team *t1, *t2;
	Meci *aux=q->front;
    while(aux!=NULL)
    {
		t1 = aux->team1;
		t2 = aux->team2;
		//Afisarea cu spatii si cratima
		//pe o linie sunt 67 de caractere, cratima e pe pozitia 33
		int nr_spaces = 67 - (strlen(t1->team_name) + strlen(t2->team_name)); // -1 de la cratima  
        int poz_cratima=strlen((t1->team_name));
		fprintf(r_out,"%s",t1->team_name);
		for(int j=0;j<nr_spaces;j++,poz_cratima++)
		{
			if(poz_cratima == 33)fprintf(r_out,"%c",'-');
			else fprintf(r_out,"%c",' ');
    	}
		fprintf(r_out,"%s\n",t2->team_name);
		aux=aux->next;
	}
}