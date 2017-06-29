#include "assign2Headers.h"

// The program will have 3 global vars: answererPid, guesserPid, and shouldRun. shouldRun should be initialized to 1.
int answererPid;
int guesserPid;
int shouldRun = 1;

void sigAlarm(int sig)
{
    kill(answererPid, TIME_OVER_SIGNAL);
    kill(guesserPid, TIME_OVER_SIGNAL);
    shouldRun = 0;
}



void sigCHLD(int sig)
{ 
    pid_t pid;
    int s;
    while( (pid=waitpid(-1,&s,WNOHANG)) > 0)
        if(WEXITSTATUS(s) == 0)
            shouldRun = 0;
}

    int main(){
    
    // Its main() install two signal handlers: one for SIGALRM and one for SIGCHLD.
        struct sigaction act;
        memset(&act,'\0',sizeof(act));
    // The SIGALRM handler will tell the two child processes to stop by sending them TIME_OVER_SIGNAL. It also sets shouldRun to 0.
        //sigaction(TIME_OVER_SIGNAL,&act,NULL);
        
    // The SIGCHLD does a waitpid() in a loop to get all finished children. It also sets shouldRun to 0.
        act.sa_handler = sigAlarm;
        act.sa_handler = sigCHLD;
        act.sa_flags		= SA_NOCLDSTOP | SA_RESTART;
        sigaction(SIGALRM,&act,NULL);
        sigaction(SIGCHLD,&act,NULL);
        
    // After installing the signal handlers, main() launches first the answering program, 
        //and then the guessing program. 
    
    // To when launching the answering program put the child pid in answererPid 
        //and have the child run the string constant ANSWERER_PROGNAME. 
        answererPid = fork();
        if  (answererPid == 0)
        {
          execl(ANSWERER_PROGNAME,ANSWERER_PROGNAME,NULL);
          fprintf(stderr,"Cannot run %s\n",ANSWERER_PROGNAME);
          exit(EXIT_FAILURE);
        }
        
        //Turn that to the string line[] with the following code:
        char	line[LINE_LEN];
        snprintf(line,LINE_LEN,"%d",answererPid);
        
    // To when launching the guessing program put the child pid in guesserPid 
        guesserPid = fork();
        
        //and have the child run the string constant GUESSER_PROGNAME. 
        if  (guesserPid == 0)
        {
          execl(GUESSER_PROGNAME,GUESSER_PROGNAME,line,NULL);
          fprintf(stderr,"Cannot run %s\n",GUESSER_PROGNAME);
          exit(EXIT_FAILURE);
        }
        
        // The guesser program must be told the process id of the answering process.
        
        
        
    	    
    // Be sure to pass line to the guesser.
    
    // Then main() sets its self up to receive SIGALRM in NUM_SECONDS seconds.
    alarm(NUM_SECONDS);
    
    // Lastly main() just does the following:
    while  (shouldRun)
      sleep(1);
    
    sleep(1);
    sleep(1);
    
    printf("launcher finished\n");
    return(EXIT_SUCCESS);
    }