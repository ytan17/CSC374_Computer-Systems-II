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
  const char* toFileCPtr;

  if (argc < 3)
  {
    fprintf(stderr, "Usage: littleCopy <fromFile> <toFile>\n");
    return(EXIT_FAILURE);
  }

  fromFileCPtr = argv[1];
  toFileCPtr = argv[2];

  /* YOUR CODE HERE */
  int	  fromFd    = open(fromFileCPtr,O_RDONLY,0);
  int	  toFd	    = open(toFileCPtr,  O_WRONLY|O_CREAT|O_TRUNC, 0660);

  if  (fromFd < 0)
  {
    fprintf(stderr,"Could not open %s\n",fromFileCPtr);
    exit(EXIT_FAILURE);
  }

  if  (toFd < 0)
  {
    fprintf(stderr,"Could not open %s\n",toFileCPtr);
    exit(EXIT_FAILURE);
  }

  char	buffer[BUFFER_LEN];
  int	numBytes;

  while  ( (numBytes = read(fromFd,buffer,BUFFER_LEN)) > 0 )
    write(toFd,buffer,numBytes);

  close(toFd);
  close(fromFd);
  return(EXIT_SUCCESS);
}
