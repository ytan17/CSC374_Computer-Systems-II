#include	<stdlib.h>
#include	<stdio.h>
#include	<signal.h>
#include	<string.h>

#define		MAX_LEN		16

void	sigIntHandler	(int		sig,
			 siginfo_t*	sigInfoPtr,
			 void*		ignoreMePtr
			)
{
  if  (sigInfoPtr->si_pid == getppid())
    printf("Hee hee!  That tickles!\n");
  else
    printf("Do I know you, MISTER!\n");
}


int	main	()
{
  pid_t	childId	= fork();

  if  (childId == 0)
  {
    struct sigaction	act;

    memset(&act,'\0',sizeof(act));
    act.sa_flags	= SA_SIGINFO;
    act.sa_sigaction	= sigIntHandler;
    sigaction(SIGINT,&act,NULL);

    while  (1)
      sleep(1);

    exit(EXIT_SUCCESS);
  }

  int	i;
  char	text[MAX_LEN];

  for  (i=0;  i<4;  i++)
  {
    printf("Press enter to tickle your Elmo:");
    fgets(text,MAX_LEN,stdin);
    kill( childId,SIGINT);
  }

  return(EXIT_SUCCESS);
}
