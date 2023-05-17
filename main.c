#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct player
    {
        char* firstName;
        char* secondName;
        int points;
        //struct player *player_next;
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

void dynamic_allocation_test(void *p){
    if(p==NULL){
        puts("Alocare dinamica esuata :(");
        exit(1);
    }
}

void open_file_test(FILE *f){
    if(f==NULL){
        printf("Eroare la deschiderea fisierului!");
        exit(1);
    }
}

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


float search_min(Team *head){ //afla punctajul minim pt echipe
    float min=head->team_points;
    while(head!=NULL){
        if(head->team_points < min)
            min = head->team_points;
        head=head->team_next;}
    return min;
}

void delete_min_from_team(Team **head, float min_points){
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

void delete_list(Team **head_team){
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


int main(int argc, char *argv[]){
    if(argc!=4){
        printf("Sintaxa initiala incorecta!");
        exit(1);
    }
    //argv[0] e lanParty
    FILE *c_in=fopen(argv[1],"r"); //deschide c.in
    open_file_test(c_in);
    FILE *d_in=fopen(argv[2],"r"); //deschide d.in
    open_file_test(d_in);
    FILE *r_out=fopen(argv[3],"w"); //deschide r.out
    open_file_test(r_out);
    int nr_teams;
    
    //Intai citim ce task trebuie sa facem (din c.in ex: 1 0 0 0 0)
    int task[4];
    for(int i=0;i<5;i++)
    fscanf(c_in,"%d",&task[i]);

    fscanf(d_in,"%d",&nr_teams);
    getc(d_in); 
    Team *head_team = (Team *) malloc(sizeof(Team));
    head_team= NULL;

    for(int i=0;i<nr_teams;i++){

        //alocarea echipei
        int nr_players; //buffer
        char team_name[50]; //buffer
        fscanf(d_in,"%d",&nr_players);
        getc(d_in);   //citeste spatiul
        fscanf(d_in,"%[^\n]",team_name); //%[^\n] tells fscanf() to read characters until it encounters a newline character ('\n') and includes whitespace characters in the string
        getc(d_in);   //citeste endline-ul
        add_Team_At_Beginning(&head_team,nr_players,team_name);
        //alocarea jucatorilor
        head_team->head_of_players=(Player *)malloc(nr_players*sizeof(Player));
        for(int j=0;j<nr_players;j++){
            char firstName[50], secondName[50];   //buffers
            int points;      //buffer
            fscanf(d_in,"%s",firstName);
            getc(d_in);   //citeste spatiul
            fscanf(d_in,"%s",secondName);
            fscanf(d_in,"%d",&(head_team->head_of_players[j].points));
            head_team->head_of_players[j].firstName=(char *) malloc((strlen(firstName)+1)*sizeof(char));
            head_team->head_of_players[j].secondName=(char *) malloc((strlen(secondName)+1)*sizeof(char));
            strcpy(head_team->head_of_players[j].firstName,firstName);
            strcpy(head_team->head_of_players[j].secondName,secondName);
            getc(d_in);
        
            /* varianta cu lista
            char firstName[50], secondName[50];   //buffers
            int points;      //buffer
            fscanf(d_in,"%s",firstName);
            getc(d_in);   //citeste spatiul
            fscanf(d_in,"%s",secondName);
            fscanf(d_in,"%d",&points);
            add_Player_At_End(&(head_team->head_of_players),points,firstName,secondName);
            getc(d_in);*/
   }
        getc(d_in);
    }
    //task 1
    //afisarea numelor echipelor in ordinea in care au intrat in fisierul r.out (adica ordinea inversa din fisierul de intrare)
    if(task[0]==1 && task[1]==0){
    Team *aux_team=(Team *)malloc(sizeof(Team));
    dynamic_allocation_test(aux_team);
    aux_team=head_team;
    while(aux_team!=NULL){
        fprintf(r_out,"%s\n",aux_team->team_name); 
        aux_team=aux_team->team_next;
    }}
    
    //task 2
    //aflam N - nr maxim de echipe ca putere a lui 2
    if(task[0]==1 && task[1]==1){
    int N=1;
    while(N*2<nr_teams)
        N*=2;
    //hai sa construim punctajul de echipa pt fiecare echipa
    Team *aux_head_team=(Team *)malloc(sizeof(Team));   
    dynamic_allocation_test(aux_head_team);   
    aux_head_team=head_team;
    while(aux_head_team!=NULL){
        aux_head_team->team_points=0;
        for(int j=0;j<aux_head_team->num_of_players;j++){
            aux_head_team->team_points+= aux_head_team->head_of_players[j].points;
        }
        aux_head_team->team_points=(aux_head_team->team_points)/(aux_head_team->num_of_players*1.0);
        aux_head_team=aux_head_team->team_next;
    }

    while(nr_teams>N && head_team){ //stergerea
    float min_points=search_min(head_team);
    delete_min_from_team((&head_team),min_points);
    nr_teams--;
    }
    //afisarea echipelor
    aux_head_team=head_team;
    while(aux_head_team!=NULL){
        fprintf(r_out,"%s\n",aux_head_team->team_name); 
        aux_head_team=aux_head_team->team_next;
    }
}
    delete_list(&head_team);
    
    fclose(c_in);
    fclose(d_in);
    fclose(r_out);
    return 0;
}