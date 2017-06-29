#include "assign2Headers.h"
// guesser.c should also have a global int shouldRun variable initialized to 1.
    int shouldRun = 1;
    
    void timeUp(int sig){
        shouldRun = 0;
    }
    void winHandler(int sig){
        shouldRun = 0;
    }
    void correctHandler(int sig)
    {
        printf("Yay! That was right!\n");
    }
    void incorrectHandler(int sig)
    {
        printf("Oops! That was wrong. Please restart from the beginning.\n");
    }
    



    int main(int argc, char* argv[]){
        char line[LINE_LEN];
        int entry;
        
        pid_t answererPid = strtol(argv[1], NULL, 10);
    // Its main() should make sure it has a command line argument (exiting with EXIT_FAILURE if not).
    //It should that argument is the process id of the answerer. 
    //Convert it from a string to an integer and hold on to its value.
    
    // Then, main() should install 4 signal handler:
        struct sigaction act;
        memset(&act,'\0',sizeof(act));
        
    // The handler for TIME_OVER_SIGNAL announces that the time is up and sets shouldRun to 0.
        act.sa_handler = timeUp;
        sigaction(TIME_OVER_SIGNAL,&act,NULL);
        
    // The handler for WIN_SIGNAL announces that the user won and sets shouldRun to 0.
        act.sa_handler = winHandler;
        sigaction(WIN_SIGNAL,&act,NULL);
        
    // The handler for CORRECT_SIGNAL announces that the user got their last guess correct.
        act.sa_handler = correctHandler;
        sigaction(CORRECT_SIGNAL,&act,NULL);
        
    // The handler for INCORRECT_SIGNAL announces that the user got their last guess wrong, and should start again from the beginning.
        act.sa_handler = incorrectHandler;
        sigaction(INCORRECT_SIGNAL,&act,NULL);
        
    // NOTE: Perhaps you can make the same handler handle both CORRECT_SIGNAL and INCORRECT_SIGNAL.
    
    
    // In a while(shouldRun) loop, allow the user to enter their next guess. 
    //If they enter 0 send the answerer ZERO_SIGNAL. If they enter 1 send the answerer ONE_SIGNAL. 
    //At after sending the signal, do a sleep(1) to give the answerer time to respond.
        
        
        do{
            printf("What would you like your next guess to be: 0 or 1? ");
            fgets(line,LINE_LEN,stdin);
            entry = strtod(line,NULL);
            //printf("%d \n",entry);
            if(entry == 0) 
                kill(answererPid,ZERO_SIGNAL);
            else if(entry == 1)
                kill(answererPid,ONE_SIGNAL);
            sleep(1);
        }while(shouldRun);
    
    // After the loop just do:
        printf("guesser finished\n");
        return(EXIT_SUCCESS);
    }