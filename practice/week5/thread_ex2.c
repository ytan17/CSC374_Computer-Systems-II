#include	<stdlib.h>
#include	<stdio.h>
#include	<pthread.h>

#define		numRabbits	10.0
#define		numTurtles	10.0
#define		rabbitGrowthRate 1.5
#define		turtleGrowthRate 1.05
int		numTimePeriods	 = 10;

struct		Animal
{
  float		population;
  float		growthRate;
};

struct Animal	rabbitPopulation	= {numRabbits,rabbitGrowthRate};
struct Animal	turtlePopulation	= {numTurtles,turtleGrowthRate};

void*  		populate	(void*	vPtr
				)
{
  struct Animal*	animalPtr	= (struct Animal*)vPtr;
  int	 		i;

  for  (i = 1;  i <= numTimePeriods;  i++)
    animalPtr->population *= animalPtr->growthRate;

  return(animalPtr);
} 


int		main		()
{
  pthread_t	rabbitThread;
  pthread_t	turtleThread;

  printf("The rabbit population starts at %g\n",rabbitPopulation.population);
  printf("The turtle population starts at %g\n",turtlePopulation.population);

  pthread_create(&rabbitThread,NULL,populate,(void*)&rabbitPopulation);
  pthread_create(&turtleThread,NULL,populate,(void*)&turtlePopulation);

  struct Animal*	animalPtr;
  pthread_join(rabbitThread,(void**)&animalPtr);
  printf("The rabbit population is now %g\n",animalPtr->population);
  pthread_join(turtleThread,(void**)&animalPtr);
  printf("The turtle population is now %g\n",animalPtr->population);
  return(EXIT_SUCCESS);
}
  

