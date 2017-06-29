#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>


char*		naughtyCopy	(const char*	fromP
				)
{
  char*	toP	= (char*)malloc(strlen(fromP)+1);
  char*	toReturn= toP;

  for ( ; *fromP != '\0'; fromP++, toP++)
    *toP = *fromP;

  *toP	= '\0';
  return(toReturn);
}


int		main		()
{
  char*	helloCPtr	= naughtyCopy("Hello class, how are you?");

  puts(helloCPtr);
  free(helloCPtr);
  return(EXIT_SUCCESS);
}
