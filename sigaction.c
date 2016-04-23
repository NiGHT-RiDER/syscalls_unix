#include<unistd.h> 
#include<signal.h>
#include<fcntl.h> 
#include<string.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<sys/types.h> 
#include<sys/stat.h> 

void handler(int);

int main(int argc, char **argv){ 

	sigset_t set,vide;
	
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_BLOCK,&set,NULL);

	char msg[256],lecture[256]; 
	int i,entree; 
	int pipef[2];
	pid_t pere,fils;

	pere = getpid();

	if(pipe(pipef) == -1){
		perror("pipe failed\n");
		exit(EXIT_FAILURE);
	}


	if((fils = fork()) < 0){
		perror("Fork failed\n");
	}

	if(fils){

		struct sigaction act;
		act.sa_handler = handler;
		act.sa_mask = vide;
		act.sa_flags = 0;

		close(pipef[0]);
		while((entree = read(0,lecture,sizeof(lecture)))> 0){ 
		sigaction(SIGUSR1,&act,NULL);
			sprintf(msg,"%s\n",lecture);
			write(1,lecture,strlen(lecture));
			write(pipef[1],lecture,entree); 
			sigsuspend(&vide);
		} 
		close(pipef[1]);

	}else{
		close(pipef[1]);
		dup2(pipef[0],0);
		execl("./sig","sig",NULL);	
		close(pipef[0]);
	}

}

void handler(int a){
	return;
}
