#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

pthread_t pid;
sem_t match,paper,tobacco,need_more;
pthread_t allthreads[4];

void* smoker_with_paper(void* para)
{
    while(1)
    {
        sem_wait(&tobacco);
        if(sem_trywait(&match) == 0)
        {
            printf("\nSmoker with paper is now smoking...");
            usleep(5);
            sem_post(&need_more);
        }
        else
            sem_post(&tobacco);
    }
}

void* smoker_with_match(void* para)
{
    while(1)
    {
        sem_wait(&paper);
        if(sem_trywait(&tobacco) == 0)
        {
            printf("\nSmoker with match is now smoking...");
            usleep(5);
            sem_post(&need_more);
        }
        else
            sem_post(&paper);
    }
}

void* smoker_with_tobacco(void* para)
{
    while(1)
    {
        sem_wait(&paper);
        if(sem_trywait(&match) == 0)
        {
            printf("\nSmoker with tobacco is now smoking...");
            usleep(5);
            sem_post(&need_more);
        }
        else
            sem_post(&paper);
    }
}

void* agent(void* para)
{
    while(1)
    {
        int num = rand() % 3;
        switch(num)
        {
            case 0: sem_post (&match);
                   sem_post (&paper);
                   break;
           case 1: sem_post (&match);
                   sem_post (&tobacco);
                   break;
           case 2: sem_post (&paper);
                   sem_post (&tobacco);
                   break;
        }
        sem_wait(&need_more);
    }
}

int main()
{
    sem_init(&match,0,1);
    sem_init(&tobacco,0,1);
    sem_init(&paper,0,1);
    sem_init(&need_more,0,1);
    
    pthread_create(&allthreads[0],NULL,smoker_with_paper,NULL);
    pthread_create(&allthreads[1],NULL,smoker_with_match,NULL);
    pthread_create(&allthreads[2],NULL,smoker_with_tobacco,NULL);
    pthread_create(&allthreads[3],NULL,agent,NULL);
    
    for(int i=0;i<4;i++)
    {
        pthread_join(allthreads[i],NULL);
    }
}