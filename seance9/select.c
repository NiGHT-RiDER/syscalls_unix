#include<unistd.h> 
#include<signal.h>
#include<fcntl.h> 
#include<string.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<sys/types.h> 
#include<sys/select.h> 
#include<sys/stat.h> 
#include<time.h>
#include<errno.h>


int main(int argc, char **argv){ 

	if(argc != 2){
		write(1,"Usage ./sel temps",17);
		return;
	}
	srand(time(NULL));



	char msg[256],lecture[256]; 
	int a,b,result,reponse,entree,temps=atoi(argv[1]); 
	int nbReussis = 0, nbMauvais = 0, nbDelaisDepasse = 0;


	fd_set rfds;
	struct timeval tv;
	int retval;


	while(1){ 

		a = (rand()%9)+1;
		b = (rand()%9)+1;
		result = a*b;
		sprintf(msg,"\n%d * %d = ",a,b);
		write(1,msg,strlen(msg));

		tv.tv_sec = temps;
		tv.tv_usec = 0;
		FD_ZERO(&rfds);
		FD_SET(0,&rfds);
		retval = select(1,&rfds,NULL,NULL,&tv);

		if(retval != 0 ){
			entree = read(0,lecture,sizeof(lecture));
			if(entree == 0){
				break;
			}
			reponse = atoi(lecture);
			if(reponse == result){
				nbReussis++;
			}else{
				nbMauvais++;
			}
		}else{
			nbDelaisDepasse++;
		}



	} 


	sprintf(msg,"\nLe nombre de bonne reponses %d .\n",nbReussis);
	write(1,msg,strlen(msg));
	sprintf(msg,"Le nombre de mauvaises reponses %d .\n",nbMauvais);
	write(1,msg,strlen(msg));
	sprintf(msg,"Le nombre de fois que le délais à été dépassé %d .\n",nbDelaisDepasse);
	write(1,msg,strlen(msg));


}
