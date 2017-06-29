#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_LEN 256

int		main		(int		argc,
				 const char*	argv[]
				)
{
  const char* fromFileCPtr;

  if (argc < 2)
  {
    fprintf(stderr, "Usage: lineCount <file>\n");
    return(EXIT_FAILURE);
  }

  fromFileCPtr = argv[1];

  /* YOUR CODE HERE */
  int	  fromFd    = open(fromFileCPtr,O_RDONLY,0);

  if  (fromFd < 0)
  {
    fprintf(stderr,"Could not open %s\n",fromFileCPtr);
    exit(EXIT_FAILURE);
  }

  char	buffer[BUFFER_LEN];
  int	numBytes;
  int	i;
  int	count	= 0;

  while  ( (numBytes = read(fromFd,buffer,BUFFER_LEN)) > 0 )
    for  (i = 0;  i < numBytes;  i++)
      if  (buffer[i] == '\n')
	count++;

  close(fromFd);
  printf("%d\n",count);
  return(EXIT_SUCCESS);
}
