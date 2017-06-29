#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>

#define		MAX_STRING	256
#define		QUIT_STRING	"exit"

int		main		()
{
  char		line[MAX_STRING];

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
