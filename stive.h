#ifndef STIVE_H
#define STIVE_H

#include "team.h"
#include "cozi.h"
struct Elem{
    Team* team;
    struct Elem *next;
};
typedef struct Elem Stack;

int isEmpty_stack(Stack* top);
Team* top_stack(Stack* top);
void push(Stack*** top, Team* team);
Team* pop(Stack** top);
void deleteStack(Stack** top);
void create_stacks(Queue *q, Stack **winners_stack, Stack** loosers_stack);
void print_Stack(Stack* top, FILE *r_out);
void create_winners_match_queue(Queue *q, Stack *head_team);

#endif // STIVE_H