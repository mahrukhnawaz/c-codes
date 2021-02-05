#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>

# define n 10

int buffer[n];
int in = 0; int out = 0;
sem_t full; sem_t empty;

void* producer(void* ptr)
{
  
  for(int i=0;i<n;i++)
  {
    sem_wait(&empty);  /* Acquire empty mutex to let consmer know data is added in the buffer */
    buffer[in] = i;  /* Add data in the buffer */
    in = (in + 1) % n;  /* Increment in */
    sem_post(&full);  /* Release full mutex let  */
  }
    
  pthread_exit(NULL);
}

void* consumer(void* ptr)
{
  for(int i=0;i<n;i++)
  {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    
    sem_wait(&full);  /* Pass through if and only if buffer is not empty. Check if there is new data in the buffer */
    printf("Data out:: %d\n",buffer[out]);  /* Print data from the buffer */
    out = (out+1) % n;  /* Increment out */
    sem_post(&empty);  /* Release empty mutex to let producer add new data in the buffer. Create Vacancy */
  }
  
  pthread_exit(NULL);
}

int main()
{
  sem_init(&full,0,0);
  sem_init(&empty,0,10);
  
  pthread_t pid[100];pthread_t cid[100];
  for(int i=0;i<100;i++)
  {
     pthread_create(&pid[i],NULL,producer,NULL);
     pthread_create(&cid[i],NULL,consumer,NULL);
  }
  for(int i=0;i<100;i++)
  {
       pthread_join(pid[i],NULL);
       pthread_join(cid[i],NULL);
  }

  
  return 0;
}