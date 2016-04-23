#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
 
#define BUF_SIZE 10
 
int main (int argc , char **argv){
    char phrase[BUF_SIZE];
    int count;
 
    /*
     *0 - stdin
     *1 - stdout
     *2 - stderr
     */
    while((count = read(0, phrase, 10)) > 0){
        if(phrase[count- 1] != '\n'){
            perror("Ligne trop lognue");
            continue;
        }
        if((write(1, phrase , count))!= count){
            perror("Erreur d'ecriture");
            exit(10);
        }  
    }
    return 0;
}
