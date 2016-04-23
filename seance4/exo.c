#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define sys(call) ((call) == -1) ? (perror(#call ": ERROR") , exit(1)) : 0

int main(int argc , char **argv){

    char ligne[80];
    pid_t process ; 
    int status;
    char *cmd[] = {"date" , "+%x - %X" , NULL};

    sprintf(ligne , "Le PID du process %s est : %d\n" , *argv ,getpid());
    sys(write(1,ligne,strlen(ligne)));

    process = fork();

    if(process == 0){

        sprintf(ligne , "PID process courant : %d ,PID parent : %d\n" , getpid() ,getppid());
        sys(write(1,ligne,strlen(ligne)));
        execvp(*cmd , cmd);

    } else if (process > 0){

        sprintf(ligne , "PID process courant : %d\nPID parent : %d\nPID fils : %d\n" , getpid() ,getppid() , process);
        sys(write(1,ligne,strlen(ligne)));
        int check ;
        sys(check = wait(&process));

        if(WIFEXITED(process)){
            int exit_status = WEXITSTATUS(status);
            sprintf(ligne , "code de sortie : %d \n" , exit_status);
            sys(write(1 , ligne , strlen(ligne)));
            sprintf(ligne , "il est : ");
            sys(write(1, ligne , strlen(ligne)));
            execvp(*cmd , cmd);
        }

    } else {
        perror("fork()");
        exit(-1);
    }

}
