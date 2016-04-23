#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>

#define BUF_SIZE 180
#define TEL_SIZE 17

typedef struct {
    char prenom[21];
    char nom[35];
    long int telephone;
} Repertoire;

/* open * read * write * close */
int main (int argc , char **argv){
    Repertoire *rep;
    char phrase[BUF_SIZE] ;
    int fd1 , fd2 , count , nb_cree , nb_modifie;
    nb_cree = nb_modifie = 0 ; 
    fprintf(stderr , "Repertoire = %d , long int = %d \n" , sizeof(Repertoire) , sizeof(long int));

    // traitement des arguments 
    if(argc != 3){
        sprintf(phrase , "Usage : %s file1 file2 \n",*argv);
        if(write(2 , phrase , strlen(phrase)) != strlen(phrase)){
            perror("ecriture");
            exit(10);
        }
    }

    // traitement des fichies 
    if((fd1 = open(*(argv + 1) , O_RDONLY)) == -1){
        perror("ouverture");
        exit(20);
    }
    if((fd2 = open(*(argv + 2) , O_WRONLY | O_TRUNC | O_CREAT , 0777)) == -1){
        perror("ouverture");
        exit(20);
    }

    // creation du repertoire 
    if((rep = malloc(sizeof(Repertoire))) == NULL ){
        perror("malloc");
        exit(30); 
    }

    while(read(fd1 , rep, 60 )> 0){
        // recupere le tel sur stdin
        nb_cree++;
        printf("%s - %s\n" ,rep->nom , rep->prenom );
        if(rep->telephone == 0){
            sprintf(phrase , "\nNom : %s \nPrenom : %s \n" , rep->nom , rep->prenom);
            if(write(1 , phrase , strlen(phrase)) != strlen(phrase)){
                perror("ecriture 1");
                exit(10);
            }
            if((count = read(0 , phrase , 17)) == -1){
                perror("read");
                exit(40);
            }
            if(phrase[count - 1] != '\n'){
                // vider le buffer
                for(count = read(0 , phrase , 1) ; count != 1 && *phrase!= '\n' ; read(0 , phrase, 1)){}
                continue;
            }
            nb_modifie++;
            int tmp = atoi(phrase);
            rep->telephone = tmp;
        } 
        if(write(fd2 , rep, sizeof(Repertoire)) == -1){
            perror("ecriture 2");
            exit(10);
        }

    }
    sprintf(phrase , "nb_cree : %d \nnb_modifie : %d\n",nb_cree , nb_modifie);
    if(write(1 , phrase , strlen(phrase)) != strlen(phrase)){
        perror("ecriture 3");
        exit(10);
    }

    // fermeture des ressources 
    close(fd1);
    close(fd2);

}
