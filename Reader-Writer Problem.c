#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex,mutey;
pthread_t tid;
pthread_t writerthreads[100];
pthread_t readerthreads[100];
int writerRequest = 0;
int readercount = 0;


void* reader(void* para)
{
    sem_wait(&mutey);
    while(writerRequest == 1);
    
    sem_wait(&mutex);
    readercount++;
    sem_post(&mutex);
    sem_post(&mutey);
    
    printf("\nReader is Reading....");
    usleep(5);
    
    sem_wait(&mutex);
    readercount--;
    sem_post(&mutex);
    
    return NULL;
}

void* writer(void* para)
{
    sem_wait(&mutey);
    while(writerRequest == 1);
    writerRequest = 1;
    sem_post(&mutey);
    
    while(readercount > 0);
    
    printf("\nWriter Entered critical section...");
    printf("\nWriter is writing...");
    usleep(5);
    printf("\nWriter left critical section...");
    
    writerRequest = 0;
}
int main()
{
    int num = 50;
    sem_init(&mutex,0,1);
    sem_init(&mutey,0,1);
    
    for(int i=0;i<num;i++)
    {
        pthread_create(&writerthreads[i],NULL,writer,NULL);
        pthread_create(&readerthreads[i],NULL,reader,NULL);
    }
    for(int i=0;i<num;i++)
    {
        pthread_join(writerthreads[i],NULL);
        pthread_join(readerthreads[i],NULL);
    }

}
