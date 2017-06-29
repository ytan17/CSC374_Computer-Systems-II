#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

#define		LINE_LEN	256
#define		COMMENT_CHAR	'#'

int		main		(int	argc,
				 char*	argv[]
				)
{
  if  (argc < 2)
  {
    fprintf(stderr,"Usage:\tintPairCounter <filePath>\n");
    exit(EXIT_FAILURE);
  }

  const char*	filePath	= argv[1];
  FILE*		filePtr		= fopen(filePath,"r");

  if  (filePtr == NULL)
  {
    fprintf(stderr,"Could not open %s\n",filePath);
    exit(EXIT_FAILURE);
  }

  char	buffer[LINE_LEN];
  int	counter	= 0;
  int	lineNum	= 0;

  while  (fgets(buffer,LINE_LEN,filePtr) != NULL)
  {
    char*	cPtr;

    lineNum++;

    for  (cPtr = buffer;  isspace(*cPtr);  cPtr++);

    if  ( *cPtr == COMMENT_CHAR  ||  *cPtr == '\0' )
      continue;

    int		i;
    int		j;

    if  ( sscanf(cPtr,"%d %d",&i,&j) == 2)
      counter++;
    else
    {
      fprintf(stderr,"Error on line %d\n",lineNum);
    }
  }

  fclose(filePtr);
  printf("%d\n",counter);
  return(EXIT_SUCCESS);
}
