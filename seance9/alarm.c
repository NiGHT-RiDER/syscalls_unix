#include<unistd.h> 
#include<signal.h>
#include<fcntl.h> 
#include<string.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include <time.h>
#include<errno.h>

void handler(int);

int main(int argc, char **argv){ 

	if(argc != 2){
		write(1,"Usage ./sel temps",17);
		return;
	}
	srand(time(NULL));

	sigset_t vide;

	sigemptyset(&vide);
	
	char msg[256],lecture[256]; 
	int a,b,result,reponse,entree,temps=atoi(argv[1]); 
	int nbReussis = 0, nbMauvais = 0, nbDelaisDepasse = 0;

	struct sigaction act;
	act.sa_handler = handler;
	act.sa_mask = vide;
	act.sa_flags = 0;


	while(1){ 
		sigaction(SIGALRM,&act,NULL);

		a = (rand()%9)+0;
		b = (rand()%9)+0;
		result = a*b;
		sprintf(msg,"\n%d * %d = ",a,b);
		write(1,msg,strlen(msg));
		alarm(temps);

		entree = read(0,lecture,sizeof(lecture));

		if(entree == 0){
			break;
		}
		if(errno == EINTR){
			nbDelaisDepasse++;
			alarm(0);
		}else{
			alarm(0);
			reponse = atoi(lecture);
			if(reponse == result){
				nbReussis++;
			}else{
				nbMauvais++;
			}
		}

	} 


	sprintf(msg,"\nLe nombre de bonne reponses %d .\n",nbReussis);
	write(1,msg,strlen(msg));
	sprintf(msg,"Le nombre de mauvaises reponses %d .\n",nbMauvais);
	write(1,msg,strlen(msg));
	sprintf(msg,"Le nombre de fois que le délais à été dépassé %d .\n",nbDelaisDepasse);
	write(1,msg,strlen(msg));


}

void handler(int a){
	printf(" Temps écoulé ! \n");	
	return;
}

