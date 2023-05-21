#ifndef TEAM_H
#define TEAM_H

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

struct player
    {
        char* firstName;
        char* secondName;
        int points;
    };
typedef struct player Player;
struct team
    {           
        int num_of_players;
        char *team_name;
        struct team *team_next;
        Player *head_of_players;
        float team_points; // punctajul de echipa

    };
typedef struct team Team;
void add_Team_At_Beginning(Team **head, int num_of_players, char *team_name);
float search_min(Team *head);
void delete_min_from_team(Team **head, float min_points);
void delete_list(Team **head_team);
void dynamic_allocation_test(void *p);
void create_Players(Team **head_team, FILE *d_in);
Team* create_aux_team(Team * head_team);  //copiaza head_team intr-o variabila auxiliara alocata dinamic
void print_teams(Team* head_team, FILE **r_out);   //afiseaza numele echipelor
void create_team_points(Team *head_team);

#endif // TEAM_H