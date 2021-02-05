#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

int main()
{
  int retval,shmid;
  void *memory = NULL;
  char *p;
  
  // Initialization
  shmid = shmget((key_t)123456789,15,IPC_CREAT | 0666);
  if(shmid < 0)
  {
    printf("\nThe creation is failed!!\n");
    return 0;
  }
  printf("\n Memory is created!!\n");
  
  //Attach Shared memory
  memory = shmat(shmid,NULL,0);
  if(p == NULL)
  {
    printf("\nAttachment Error!!\n");
    //return 0;
  }
  p = (char*) memory;
  
  //reading data from memory
  printf("\nMessage is:: %s",p);
  
    //Detach
    retval = shmdt(p);
  
  return 0;
}