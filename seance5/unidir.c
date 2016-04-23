#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define sys(call) ((call) == -1) ? (perror(#call ": ERROR") , exit(1)) : 0 

int main(int argc , char **argv){
    int pipefd[2] , buf;
    pid_t cpid;
    char ligne [80];
    size_t size;

    assert(argc == 1);

    sys(pipe(pipefd));
    sys(cpid = fork());

    if (cpid == 0) {    /* Le fils lit dans le pipe */
        close(pipefd[1]);
        while((buf = read(pipefd[0] , ligne , 80))){
            if(buf == -1){
                perror("lecture");
                exit(1);
            }
            ligne[buf] = '\0';
            printf("FILS : %s \n" , ligne);
        }
        close(pipefd[0]);
    } else {                    /* Le père écrit dans le pipe */
        close(pipefd[0]);
        while(fgets(ligne ,80 , stdin)){
            printf("PERE : %s\n" , ligne);
            sys(write(pipefd[1] , ligne , strlen(ligne)));
        }
        close(pipefd[1]);
    }
    exit(0);
}

