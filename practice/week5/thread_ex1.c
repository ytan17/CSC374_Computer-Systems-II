/* Compile with:
 * gcc -lpthread thread_ex1.c -o thread_ex1
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
const int N = 2;

/* thread routine */
void *thread_routine(void *vargp)
{
    int id = *(int*)vargp;
    const char* ptr;
    printf("Hello from child thread %d\n", id);
    switch (id)
        {
      case 0:     ptr = "Hello "; break;
      case 1:     ptr = "there!"; break;
        }
    return((void*)ptr);
}

int main()
{
    int         i;
    const char* msgPtr;
    pthread_t   tid[N];
    int		index[N];

    for (i = 0; i < N; i++)
    {
	index[i] = i;
        pthread_create (&tid[i], NULL, thread_routine, (void *)&index[i]);
    }

    for (i = 0; i < N; i++)
    {
        pthread_join(tid[i], (void**)&msgPtr);
        printf("%s\n",msgPtr);
    }

    return(0);
}





