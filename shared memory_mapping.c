#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<wait.h>

int main()
{
	
	if(fork()==0)
	{
	
		int i;
		while(i=shmget(5465,1024,0)<0);
		char* ptr =(char*)shmat(i,(void*)0x0000080000000000,0); 
		
		printf("Child Process: Shared memory is mapped at %ld\n",(long)ptr);
		
		sprintf(ptr,"Hello World");	
	
	}
	else
	{
	
		int i = shmget(5465,1024,0666|IPC_CREAT); if(i<0) printf("Shared memory not created");
		char* ptr =(char*)shmat(i,(void*)0x0000080000000000,0); 
		
		printf("Parent Process: Shared memory is mapped at %ld\n",(long)ptr);
		
		wait(NULL);
	
		printf("%s",ptr);
	
		
	}
	
	
	return 0;
}