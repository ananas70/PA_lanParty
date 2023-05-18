#ifndef STIVE_H
#define STIVE_H

#include "team.h"

struct Elem{
    Team* team;
    struct Elem *next;
};
typedef struct Elem Node;

int isEmpty_stack(Node* top);
Team* top(Node* top);
void push(Node** top, Team* team);
Team* pop(Node** top);
void deleteStack(Node** top);


#endif // STIVE_H