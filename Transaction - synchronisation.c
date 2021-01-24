#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_deposit,sem_withdrawl,sem_reader;

pthread_t deposits[100],withdrawls[100];

struct bankdata{
    int balance;
};

struct bankdata mydata;
mydata.balance = 5000;

//Deposit
int get_balance()
{
    usleep(5);
    return mydata.balance;
}
int deposit_Amount(int amount)
{
    return mydata.balance + amount;
}
void update_Balance(int amount)
{
    mydata.balance = amount;
}
void* deposit(void* param)
{
    int a = 0; int amount = 0;
    while(1)
    {
        a = rand() % 1000;
        if(sem_trywait(&sem_reader))
        {
            amount = get_balance();
            sem_wait(&sem_deposit);
            amount = deposit_Amount(amount);
            update_Balance(amount);
            usleep(5);
            printf("\nSomeone just deposited amount...");
            sem_post(&sem_reader);
            sem_post(&sem_deposit);
        }
    }
}
//withdrawl
int withdrawl_Amount(int amount)
{
    if(amount <= mydata.balance)
        return mydata.balance - amount;
    return 0;
}
void* withdrawl(void* param)
{
    
    int a = 0; int amount = 0;
    while(1)
    {
        a = (rand() % 1000)-1000;
        if(sem_trywait(&sem_reader))
        {
            amount = get_balance();
            sem_wait(&sem_withdrawl);
            amount = withdrawl_Amount(amount);
            update_Balance(amount);
            usleep(5);
            printf("\nSomeone just withdrawl amount...");
            sem_post(&sem_withdrawl);
            sem_post(&sem_reader);
        }
    }
}

int main()
{
    sem_init(&sem_reader,0,1);
    sem_init(&sem_withdrawl,0,1);
    sem_init(&sem_deposit,0,1);

    for(int i=0;i<100;i++)
    {
        pthread_create(&deposits[i],NULL,deposit,NULL);
        pthread_create(&withdrawls[i],NULL,withdrawl,NULL);
    }
    for(int i=0;i<100;i++)
    {
        pthread_join(deposits[i],NULL);
        pthread_join(withdrawls[i],NULL);
    }
}
