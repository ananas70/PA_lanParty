#include "team.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void add_Team_At_Beginning(Team **head, int num_of_players, char *team_name)
{
	Team* newNode = (Team*)malloc(sizeof(Team));
    dynamic_allocation_test(newNode);
	//newNode->val = v;
    newNode->num_of_players=num_of_players;
    newNode->team_name=(char *) malloc((strlen(team_name)+1)*sizeof(char));
    strcpy(newNode->team_name,team_name);
	newNode->team_next = *head;
	*head = newNode;
}

float search_min(Team *head)
{ //afla punctajul minim pt echipe
    float min=head->team_points;
    while(head!=NULL){
        if(head->team_points < min)
            min = head->team_points;
        head=head->team_next;}
    return min;
}

void delete_min_from_team(Team **head, float min_points)
{
    //lista goala
    if(*head==NULL)return; 
    //elem sters e capul listei
    Team* head_copy = (Team*)malloc(sizeof(Team));
    head_copy=*head;
    if(head_copy->team_points==min_points){
     *head=(*head)->team_next;
     free(head_copy);
     return;}
    //elementul sters are o pozitie oarecare
    Team *prev=(Team*)malloc(sizeof(Team));
    prev=*head;
    while(head_copy!=NULL){
        if(head_copy->team_points==min_points){
            prev->team_next=head_copy->team_next;
            free(head_copy);
            return;
        }
        else {
            prev=head_copy;
            head_copy=head_copy->team_next;
        }
    }
}

Team* create_aux_team(Team * head_team){   //copiaza head_team intr-o variabila auxiliara alocata dinamic
    Team *aux_team=(Team *)malloc(sizeof(Team));
    dynamic_allocation_test(aux_team);
    aux_team=head_team;
    return aux_team;
}

void delete_list(Team **head_team)
{
    //eliberarea memoriei
    //eliberezi intai copiii si dupa aia blocul cel mare
    Team *aux_team;
    while(*head_team!=NULL){
        aux_team=(*head_team)->team_next;
        free(*head_team);
        *head_team=aux_team;
    }
    
    *head_team=NULL;
}

void dynamic_allocation_test(void *p)
{
    if(p==NULL){
        puts("Alocare dinamica esuata :(");
        exit(1);
    }
}

void create_Players(Team **head_team, FILE *d_in)
{
    int nr_players=(*head_team)->num_of_players;
     (*head_team)->head_of_players=(Player *)malloc(nr_players*sizeof(Player));
        for(int j=0;j<nr_players;j++){
            char firstName[50], secondName[50];   //buffers
            int points;      //buffer
            fscanf(d_in,"%s",firstName);
            getc(d_in);   //citeste spatiul
            fscanf(d_in,"%s",secondName);
            fscanf(d_in,"%d",&((*head_team)->head_of_players[j].points));
            (*head_team)->head_of_players[j].firstName=(char *) malloc((strlen(firstName)+1)*sizeof(char));
            (*head_team)->head_of_players[j].secondName=(char *) malloc((strlen(secondName)+1)*sizeof(char));
            strcpy((*head_team)->head_of_players[j].firstName,firstName);
            strcpy((*head_team)->head_of_players[j].secondName,secondName);
            getc(d_in);
}}

void print_teams(Team* head_team, FILE **r_out)   //afiseaza numele echipelor
{
     while(head_team!=NULL)
     {
        fprintf(*r_out,"%s\n",head_team->team_name); 
        head_team=head_team->team_next;
    }
}

void create_team_points(Team *head_team)
{
    while(head_team!=NULL){
        head_team->team_points=0;
        for(int j=0;j<head_team->num_of_players;j++){
            head_team->team_points+= head_team->head_of_players[j].points;
        }
        head_team->team_points=(head_team->team_points)/(head_team->num_of_players*1.0);
        head_team=head_team->team_next;
    }
}