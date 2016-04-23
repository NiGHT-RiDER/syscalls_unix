#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define SYS(call)((call) == -1) ? (perror(#call ": ERROR") , exit(1)) : 0

int main (int argc , char **argv){

    pid_t pid_process = fork();
    char ligne[80];

    if(pid_process > 0){ // parent 
        int status;
        if(wait(&status) == -1){
            perror("wait()");
            exit(3);
        }
        else{
            /*enfant termine de maniere normale ?*/
            if(WIFEXITED(status)){
                sprintf(ligne , "%d a quitte avec le code de sortie %d btw pere est %d\n",getpid(), status , getppid());
                SYS(write(1 , ligne , strlen(ligne)));
            }
            sprintf(ligne,"1 2 3\n");
            SYS(write(1 , ligne , strlen(ligne)));
        }
    } else if(pid_process == 0){ 
        sprintf(ligne,"4 5 6\n");
        SYS(write(1 , ligne , strlen(ligne)));
        exit(2);
    } else { 
        perror("erreur fork");
        exit(1);
    }

}
