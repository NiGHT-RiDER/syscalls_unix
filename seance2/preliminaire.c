#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>

int main (int argc , char **argv){
    char ligne[11] , message[80];
    int chars_lu , nb_read;
    nb_read = 0;
    char *input = "Introduire le message  ";

    while(1){
        if(write(1 , input , strlen(input)) != strlen(input)){
            perror("1");
            exit(1);
        }
        if((chars_lu = read(0 , ligne , 10)) < 1){
            if(chars_lu == 0){
                break;
            }
            perror("3");
            exit(3);
        }
        nb_read++;
        ligne[chars_lu] = '\0';
        sprintf(message , "%d characteres lu : %s\n" , chars_lu , ligne);
        if(write(1 , message , strlen(message)) != strlen(message)){
            perror("2");
            exit(2);
        }
    }
    sprintf(message , "%d appels a read \n" , nb_read);
    if(write(1 , message , strlen(message)) != strlen(message)){
        perror("3");
        exit(3);
    }



}
