#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<signal.h>

int		main		()
{
  struct sigaction act;

  memset(&act,'\0',sizeof(struct sigaction));
  act.sa_handler = SIG_IGN;// Ignore SIGINT
  sigaction(SIGINT,&act,NULL);

  do
  {
    printf("You can't stop me!  You can't stop me!  Ngyeah!  Ngyeah!\n");
    sleep(1);
  }
  while  (1);

  return(EXIT_SUCCESS);
}
