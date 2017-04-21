#include "util.h"

#define SYS_WRITE 4
#define SYS_READ 3 
#define STDOUT 1
#define STDIN 0
#define STDERR 2

int main (int argc , char* argv[], char* envp[])
{
  
  char buffer[256];
  int size = system_call(SYS_READ,STDIN,buffer,256);
  int debug = 0;
  int write;
  int j;
  for(j=1;j<argc;j++){
      if(strcmp(argv[j],"-d")==0)
          debug = 1;
  }
  while(size > 0){
  int i;
  for(i=0;i<size;i++){
    if (buffer[i] >='A' && buffer[i] <= 'Z')
        buffer[i] += 32;
  }
  write = system_call(SYS_WRITE,STDOUT,buffer,size);
  if(debug){
      system_call(SYS_WRITE,STDERR,itoa(SYS_READ),4);
      system_call(SYS_WRITE,STDERR,itoa(size),4);
      system_call(SYS_WRITE,STDERR,"\n",1);
      system_call(SYS_WRITE,STDERR,itoa(SYS_WRITE),4);
      system_call(SYS_WRITE,STDERR,itoa(write),4);
      system_call(SYS_WRITE,STDERR,"\n",1);
  }
  size = system_call(SYS_READ,STDIN,buffer,256);
  }
  return 0;
}
