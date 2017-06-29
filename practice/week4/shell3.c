#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<signal.h>


#define		MAX_STRING	256
#define		QUIT_STRING	"exit"

void		sigChildHandler	(int	sig
				)
{
  pid_t	pid;
  int	s;

  while( (pid=waitpid(-1,&s,WNOHANG)) > 0)
    if (WIFEXITED(s) != 0)
      printf("%d returned %d\n",pid,WEXITSTATUS(s));
    else
      printf("%d crashed!\n",pid);
}


int		main		()
{
  char		line[MAX_STRING];

  struct sigaction	act;

  memset(&act,'\0',sizeof(act));
  act.sa_handler	= sigChildHandler;
  act.sa_flags		= SA_NOCLDSTOP | SA_RESTART;
  sigaction(SIGCHLD,&act,NULL);

  while  (1)
  {
    printf("What program would you like to run (or '%s' to quit)? ",
	   QUIT_STRING
	  );
    fgets(line,MAX_STRING,stdin);

    char*	cPtr	= strchr(line,'\n');

    if  (cPtr != NULL)
      *cPtr = '\0';

    if  (strcmp(line,QUIT_STRING) == 0)
      break;

    pid_t	pid	= fork();

    if  (pid == 0)
    {
      execl(line,line,NULL);
      fprintf(stderr,"Cannot run %s\n",line);
      exit(EXIT_FAILURE);
    }
  }

  return(EXIT_SUCCESS);
}
