#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define VALUE 5000000
int sum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* SUM_IT(void* arg)
{
  int val = *(int*)arg;
  for(int i=0; i < VALUE;i++)
  {
    // the critical section
    
    // start - Acquire Lock
    pthread_mutex_lock(&mutex);
    
    sum += val;
    
    pthread_mutex_unlock(&mutex);
    //end - Release Lock
  }
  
  return (void*)(long)sum;
}

int main()
{
  int a = 1;  int b = -1;

  pthread_t tid[2];

  pthread_create(&tid[0],NULL,SUM_IT,&a);
  pthread_create(&tid[1],NULL,SUM_IT,&b);
  
  pthread_join(tid[0],NULL);
  pthread_join(tid[1],NULL);
  
  printf("\nAnswer is:: %d\n\n",sum);
  
  return 0;
}