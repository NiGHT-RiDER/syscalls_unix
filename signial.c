#include<unistd.h> 
#include<fcntl.h> 
#include<string.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<sys/types.h> 
#include<sys/stat.h> 

int main(int argc, char **argv){ 


	char msg[250],lecture[250]; 
	int i,entree,lues=0; 



	while((entree = read(0,lecture,sizeof(lecture)))> 0){ 
		
		for(i=0;i<entree;i++)
		   msg[i]=lecture[entree-i-2];

		sprintf(lecture,"%s \n",msg);
		write(1,lecture,strlen(lecture)); 
		kill(getppid(),10);
		lues++;
	} 

	if(entree <= 0){
		sprintf(msg,"Le nombre de ligne traité est %d \n",lues);
		write(1,msg,strlen(msg)); 	
	}
}
