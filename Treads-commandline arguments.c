#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/wait.h>
#include <pthread.h>

struct data
{
  int *arr;
  int size;
};

void* assendingOrder(void* argv)
{
    struct data ptr1 = (*(struct data*)argv);
    int a;
    
    for (int i = 0; i < ptr1.size; ++i) 
        {
 
            for (int j = i + 1; j < ptr1.size; ++j)
            {
 
                if (ptr1.arr[i] > ptr1.arr[j]) 
                {
 
                    a =  ptr1.arr[i];
                    ptr1.arr[i] = ptr1.arr[j];
                    ptr1.arr[j] = a;
 
                }
 
            }
 
        }
    printf("\nAssending Sorted::");
    for(int i=0;i<ptr1.size;i++)
    {
        printf("%d,",ptr1.arr[i]);
    }
}
void* decsendingOrder(void* argv)
{
    struct data ptr1 = (*(struct data*)argv);
    int a;
    
    for (int i = 0; i < ptr1.size; ++i) 
        {
 
            for (int j = i + 1; j < ptr1.size; ++j)
            {
 
                if (ptr1.arr[i] < ptr1.arr[j]) 
                {
 
                    a =  ptr1.arr[i];
                    ptr1.arr[i] = ptr1.arr[j];
                    ptr1.arr[j] = a;
 
                }
 
            }
 
        }
    printf("\nDesending Sorted::");
    for(int i=0;i<ptr1.size;i++)
    {
        printf("%d,",ptr1.arr[i]);
    }
}
void* calculate_avg(void *ptr)
{
    struct data ptr1 = (*(struct data*)ptr);
    float *avg = 0;
    for(int i=0 ; i < ptr1.size ; i++)
    {
        *avg += ptr1.arr[i];
    }

    *avg = *avg/ptr1.size-1;
    printf("\nAverage :: %f",*avg);
}
void* searchnum(void *ptr)
{
    struct data ptr1 = (*(struct data*)ptr);
    int a;
    printf("\nEnter number::");
    scanf("%d",&a);
    for(int i=0 ; i < ptr1.size ; i++)
    {
        if(ptr1.arr[i] == a)
        {
            printf("\nNumber is found.");
            return NULL;
        }
    }
    printf("\nNumber didn't found.");
}
int main(int c,char* argv[])
{
    int arr[c-1];
    for(int i=0,j=1;i<c-1;i++,j++)
    {
        arr[i] = atoi(argv[j]);
        printf("%d,",arr[i]);
    }
    
    struct data mydata;
    mydata.arr = arr;
    mydata.size = c-1;
    pthread_t tid[4];
    
    pthread_create(&tid[0],NULL,assendingOrder,&mydata);
    pthread_create(&tid[1],NULL,decsendingOrder,&mydata);
    pthread_create(&tid[2],NULL,calculate_avg,&mydata);
    pthread_create(&tid[3],NULL,searchnum,&mydata);
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);

    return 0;
}
