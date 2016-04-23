#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<assert.h>
#include<time.h>

#define MAX 9
#define MIN 1

static int nb_reussis = 0;
static int nb_ecoule  = 0;
static int nb_echoue  = 0;

void sig_handler(int signal){
    switch(signal){
        case SIGALRM : 
            nb_ecoule++;
            printf("TEMPS ECOULE \n");
            break;
        default :
            break;
    }
}

int main(int argc , char **argv){

    // check args 
    assert(argc == 2);
    srand(time(NULL));

    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sa.sa_flags = SA_RESTART;    

    if(sigaction(SIGALRM , &sa , NULL) == -1){
        perror("cannot handle SIGALRM \n");
        exit(1);
    }

    int temps_limite = atoi(argv[1]);
    char ligne[80];
    printf("Entrez enter pour commencer :)\n");

    for(alarm(temps_limite);fgets(ligne , 80 , stdin) != NULL; alarm(temps_limite)){
        int a = (rand() % (MAX - MIN + 1)) + MIN ;
        int b = (rand() % (MAX - MIN + 1)) + MIN ;
        int res = a * b ;
        printf(" %d * %d = ?\n" , a , b );
        fgets(ligne , 80 , stdin);
        int res_user = atoi(ligne);
        if(res_user == res){
            printf("REUSSI\n");
            nb_reussis++;
        } else if (res_user != res) {
            printf("ECHOUE\n");
            nb_echoue++; 
        }
        printf("Entrez sur enter pour continuer\n");
    } 
    printf("--- RESULTATS ---\n");
    printf("reussis : %d\n" , nb_reussis);
    printf("echoue  : %d\n" , nb_echoue);
    printf("ecoule  : %d\n" , nb_ecoule);
}
