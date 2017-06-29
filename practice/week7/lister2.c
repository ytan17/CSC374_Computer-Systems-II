#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<sys/stat.h>
#include	<unistd.h>

#define		LINE_LEN	256

int		main		(int	argc,
				 char*	argv[]
				)
{
  const char*	dirName	= (argc < 2) ? "." : argv[1];
  DIR*		dirPtr	= opendir(dirName);

  if  (dirPtr == NULL)
  {
    fprintf(stderr,"Cannot open %s\n",dirName);
    exit(EXIT_FAILURE);
  }

  struct dirent*	entryPtr;

  while  ( (entryPtr = readdir(dirPtr)) != NULL )
  {
    char	fullPath[LINE_LEN];
    struct stat	statBuffer;

    snprintf(fullPath,LINE_LEN,"%s/%s",dirName,entryPtr->d_name); 
    stat(fullPath,&statBuffer);

    if  ( S_ISREG(statBuffer.st_mode) )
      printf("%s (%lu bytes)\n",entryPtr->d_name,statBuffer.st_size);
    else
    if  ( S_ISDIR(statBuffer.st_mode) )
      printf("%s (dir)\n",entryPtr->d_name);
    else
      printf("%s (other)\n",entryPtr->d_name);
    
  }

  closedir(dirPtr);
  return(EXIT_SUCCESS);
}
