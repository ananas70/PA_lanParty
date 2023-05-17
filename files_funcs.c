#include "files.h"

void open_file_test(FILE *f)
{
    if(f==NULL){
        printf("Eroare la deschiderea fisierului!");
        exit(1);
    }
}

void open_files(FILE **c_in, FILE **d_in, FILE **r_out, int argc, char *argv[]){
    //verificare sintaxa
     if(argc!=4){
        printf("Sintaxa initiala incorecta!");
        exit(1);
    }
    //deschiderea fisierelor
    //argv[0] = lanParty, argv[1] = c.in, argv[2] = d.in, argv[3] = fisier de output
    *c_in=fopen(argv[1],"r"); //deschide c.in
    open_file_test(*c_in);
    *d_in=fopen(argv[2],"r"); //deschide d.in
    open_file_test(*d_in);
    *r_out=fopen(argv[3],"w"); //deschide r.out
    open_file_test(*r_out);
}

void close_files(FILE **c_in, FILE **d_in, FILE **r_out)
{
    fclose(*c_in);
    fclose(*d_in);
    fclose(*r_out);
}