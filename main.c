#include "team.h"
#include "files.h"
#include "stive.h"
#include "cozi.h"
#include "tree.h"

int main(int argc, char *argv[]){
    FILE *c_in, *d_in, *r_out;
    open_files(&c_in, &d_in, &r_out, argc, argv);   //deschiderea fisierelor
    // c_in=fopen("date/t10/c.in","r");
    // if(c_in==NULL)
    // {
    //     printf("eroare fisiere");
    //     exit(1);
    // }
    // d_in=fopen("date/t10/d.in","r");
    // if(d_in==NULL)
    // {
    //     printf("eroare fisiere");
    //     exit(1);
    // }
    // r_out=fopen("r_out","w");
    // if(r_out==NULL)
    // {
    //     printf("eroare fisiere");
    //     exit(1);
    // }

    int nr_teams;
    //Intai citim ce task trebuie sa facem (din c.in ex: 1 0 0 0 0)
    int task[4];
    for(int i=0;i<5;i++)
        fscanf(c_in,"%d",&task[i]);
    //Citim din fisierul cu echipele
    fscanf(d_in,"%d",&nr_teams);
    getc(d_in); 
    Team *head_team = (Team *) malloc(sizeof(Team));
    head_team= NULL;

    for(int i=0;i<nr_teams;i++){
        //alocarea echipei
        int nr_players; char team_name[50]; //buffers
        fscanf(d_in,"%d",&nr_players);
        getc(d_in);   //citeste spatiul
        fscanf(d_in,"%[^\n]s",team_name);
        team_name[strlen(team_name)-1] = '\0';
        if(team_name[strlen(team_name)-1] == ' ')
            team_name[strlen(team_name)-1] = '\0';
        //printf("%s\n",team_name);
        getc(d_in);   //citeste endline-ul
        add_Team_At_Beginning(&head_team,nr_players,team_name);

        //alocarea jucatorilor
        head_team->head_of_players=(Player *)malloc(nr_players*sizeof(Player));
        create_Players(&head_team,d_in);
        getc(d_in);
    }
    //TASK 1
    //afisarea numelor echipelor in ordinea in care au intrat in fisierul r.out (adica ordinea inversa din fisierul de intrare)
    if(task[1]==0)
        print_teams(head_team, &r_out);
    
    //TASK 2
    else 
    {
        //aflam N - nr maxim de echipe ca putere a lui 2
        //retinem Nr_rounds pt task-ul 3
        int N=1,Nr_rounds=0;
        while(N*2<=nr_teams)
            N*=2, Nr_rounds++;
        //construim punctajul de echipa pt fiecare echipa
        create_team_points(head_team);
        while(nr_teams>N && head_team)  //stergerea
        {
            float min_points=search_min(head_team);
            delete_min_from_team((&head_team),min_points);
            nr_teams--;
        }
        
        //afisarea echipelor
        print_teams(head_team, &r_out);
        if(task[2]==0)return 0;
        // TASK 3
        fprintf(r_out,"\n"); //trebuie un endline dupa echipe
        int k=1;
        //Cream coada cu meciurile
        Queue *q = create_empty_Queue();
        create_match_queue(q,head_team);
        Node *root = (Node *)malloc(sizeof(Node)); //pt TASK 4
        while(k<=Nr_rounds)
        {
            //Afisam meciurile din runda
            fprintf(r_out, "--- ROUND NO:%d\n",k);
            print_queue(q,r_out);
            fprintf(r_out,"%c",'\n');
             //Cream stivele
            Stack *winners_stack=(Stack *)malloc(sizeof(Stack));
            Stack *losers_stack=(Stack *)malloc(sizeof(Stack));
            winners_stack=NULL;
            losers_stack=NULL;
            create_stacks(q,&winners_stack,&losers_stack); //atentie ca goleste coada
            //TASK 4
            if(k == Nr_rounds-3)
            {
            root = create_last_8_tree(winners_stack);
            }
            //Golim stiva de invinsi
            deleteStack(&losers_stack);
            //Cream coada de meciuri din runda urmatoare
            create_winners_match_queue(q,winners_stack);
            //Afisam castigatorii rundei (stiva castigatorilor)
            fprintf(r_out, "WINNERS OF ROUND NO:%d\n",k);
            print_Stack(winners_stack, r_out);
            k++;
        }
        if(task[3]==1)
        {
            fprintf(r_out,"\nTOP 8 TEAMS:\n");
            DRS(root,r_out);
        }

    }
    delete_list(&head_team);
    close_files(&c_in, &d_in, &r_out);
    return 0;
}