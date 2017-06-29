#include	<stdlib.h>
#include	<stdio.h>
#include	<signal.h>
#include	<string.h>

#define		LINE_LEN	16

int		shouldRun	= 1;

void		sigAlarmHandler	(int	sig
				)
{
  shouldRun	= 0;
}


void		sigIntHandler	(int	sig
				)
{
  int	numSecs	= alarm(0);
  char	line[LINE_LEN];

  printf("%d seconds remain, press enter to continue:",numSecs);
  fgets(line,LINE_LEN,stdin);
  alarm(numSecs);
}


int		main		()
{
  int		numSecs;
  char		line[LINE_LEN];

  printf("Please enter the number of seconds before the alarm goes off: ");
  fgets(line,LINE_LEN,stdin);
  numSecs	= strtol(line,NULL,10);

  struct sigaction	act;

  memset(&act,'\0',sizeof(act));
  act.sa_handler	= sigAlarmHandler;
  sigaction(SIGALRM,&act,NULL);
  act.sa_handler	= sigIntHandler;
  sigaction(SIGINT,&act,NULL);

  alarm(numSecs);


  while  (shouldRun)
    printf("Tick tock\n");

  printf("Ding Ding Ding!\n");
  return(EXIT_SUCCESS);
}
