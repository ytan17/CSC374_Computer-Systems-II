#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>


char*		naughtyCopy	(const char*	fromP,
				 size_t		n
				)
{
  size_t	len	= strlen(fromP);
  size_t	copyLen	= (n < (len+1)) ? n : (len+1);
  char*	toP	= (char*)malloc(copyLen);
  char*	toReturn= toP;

  for (; copyLen > 1; fromP++, toP++, copyLen--)
    *toP = *fromP;

  *toP	= '\0';
  return(toReturn);
}


int		main		()
{
  int i;

  for  (i = 100;  i > 0;  i--)
  {
    char*	helloCPtr	= naughtyCopy("Hello class, how are you?",i);

    puts(helloCPtr);
    free(helloCPtr);
  }

  return(EXIT_SUCCESS);
}
