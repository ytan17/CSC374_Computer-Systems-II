#include<stdlib.h>
#include<stdio.h>
#include <string.h>

#define MAX_LINE 264

struct		Word
{
  char*		textPtr_;
  struct Word*	nextPtr_;
};

/*
(1) find the end of the word with a loop.  Stop at a comma or '\0'.
(2) malloc a new 'struct Word'
(3) malloc space for the string you just found
(4) copy the string into that space, and add the ending '\0'
(5) compute the value of the nextPtr_ member var?
    (Say, don't we already have function that computes and returns a Struct Word?)
    Where does the next string begin?
(6) return the address of the 'struct Word' you just made
*/

struct Word* obtainCommaSeparatedList (const char* start){

    const char* charRun = start;
    if(*charRun == '\0') return NULL;
    
    struct Word*	toReturn	= (struct Word*)malloc(sizeof(struct Word));
    for(charRun = start;*charRun != '\0' && *charRun != ',';charRun++);
    
    //taking the word
    toReturn->textPtr_ = malloc(charRun - start + 1);
    //make a copy of the word
    strncpy(toReturn->textPtr_,start,charRun - start);
    //add ending '\0'
    toReturn->textPtr_[charRun-start] = '\0';
    
    //recursion
    toReturn->nextPtr_ = obtainCommaSeparatedList(charRun+1);
    
    return toReturn;


    
}

void printCommaSeparatedList (const struct Word* list){
  if(list == NULL) return;
  printf("%s\n",list->textPtr_);
  printCommaSeparatedList(list->nextPtr_);
}

void freeCommaSeparatedList (struct Word* list){

  if(list == NULL) return;
  free(list->textPtr_);
  freeCommaSeparatedList(list->nextPtr_);
  free(list);
}

int main(){
  char line[MAX_LINE];
  
  printf("please enter a line of text: ");
  fgets(line,MAX_LINE,stdin);

  //remove new line charater
  char*		cPtr	= strchr(line,'\n');
  if  (cPtr != NULL)
    *cPtr = '\0';
  
  struct Word* LinkedList = obtainCommaSeparatedList(line);
  printCommaSeparatedList(LinkedList);
  freeCommaSeparatedList(LinkedList);

    
  return(EXIT_SUCCESS);
 
}