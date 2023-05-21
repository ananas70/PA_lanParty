#ifndef COZI_H
#define COZI_H
#include "team.h"

struct meci{
    Team *team1, *team2;
    struct meci *next;
};
typedef struct meci Meci;

struct Q {
    Meci *front, *rear;
};
typedef struct Q Queue;

int isEmpty_Q(Queue*q);
Queue* create_empty_Queue();
void enQueue(Queue* q, Team* t1, Team* t2);
void deQueue(Queue* q, Team **team1, Team **team2);  //returneaza meciurile prin referinta
void deleteQueue(Queue* q);
void create_match_queue(Queue *q, Team *head_team);
void print_queue(Queue *q, FILE* r_out);


#endif //COZI_H