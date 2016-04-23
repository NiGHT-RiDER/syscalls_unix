#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define sys(call) ((call) == -1) ? (perror(#call ": ERROR") , exit(1)) : 0 

int main(int argc , char **argv){
    assert(argc = 1);

    int pipe1[2] , pipe2[2] , char_count , line_count;
    pid_t current_pid;
    char ligne[256];

    sys(pipe(pipe1));
    sys(pipe(pipe2));
    sys(current_pid = fork());
    
    line_count = 0;

    if(current_pid == 0){
        close(pipe1[1]);
        close(pipe2[0]);

        char_count = 0;
        while((char_count = read(pipe1[0] , ligne , 256))){
            sys(write(pipe2[1] , ligne , char_count));
        }

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);

    } else {
        close(pipe1[0]); 
        close(pipe2[1]); 

        char_count = 0;
        while((char_count = read(0 , ligne , 256))){
            ligne[char_count] = '\0';
            sys(write(pipe1[1] , ligne , strlen(ligne)));
            line_count++;
            char_count = read(pipe2[0] , ligne , 256);
            printf("ligne recu de fils %s\n" , ligne);
        }
    } 

    printf("recu de mon fils : le fils a traite %d lignes \n" ,line_count );
    close(pipe1[1]);
    close(pipe2[0]);
    wait(NULL);
    exit(0);

}
