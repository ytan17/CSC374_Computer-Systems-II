#include	<stdlib.h>
#include	<stdio.h>

int		data		= 1;

int		bss		= 0;

int		main		()
{
  int*		iPtr		= (int*)malloc(sizeof(int));
  int		stack		= 2;
  *iPtr				= 5;

  pid_t		pid		= fork();

  if  (pid == 0)
  {
    data++;
    bss++;
    (*iPtr)++;
    stack++;
  }
  else
  {
    data--;
    bss--;
    (*iPtr)--;
    stack--;
  }

  printf("pid %d: data = %d, bss = %d, heap = %d, stack = %d\n",
	 getpid(),data,bss,*iPtr,stack
	);
  free(iPtr);
  return(EXIT_SUCCESS);
}
