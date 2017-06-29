#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<signal.h>

void		handle		(int	sig
				)
{
  switch  (rand() % 4)
  {
  case 0 :
    printf("Stop that!\n");
    break;
  case 1 :
    printf("Ouch!\n");
    break;
  case 2 :
    printf("Help!\n");
    break;
  case 3 :
    printf("Don't do that!\n");
    break;
  }
}


int		main		()
{
  struct sigaction act;

  memset(&act,'\0',sizeof(struct sigaction));
  act.sa_handler = handle;// Ignore SIGINT
  sigaction(SIGINT,&act,NULL);

  do
  {
    printf("You can't stop me!  You can't stop me!  Ngyeah!  Ngyeah!\n");
    sleep(1);
  }
  while  (1);

  return(EXIT_SUCCESS);
}
