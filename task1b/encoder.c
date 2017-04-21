#include "util.h"

#define SYS_WRITE 4
#define SYS_READ 3 
#define SYS_OPEN 5
#define STDOUT 1
#define STDIN 0
#define STDERR 2


int main (int argc , char* argv[], char* envp[])
{
  
  char buffer[256];
  int debug = 0;
  int input = STDIN; 
  int output = STDOUT;
  int j,write;
  for(j=1;j<argc;j++){
      if(strcmp(argv[j],"-o")==0){
          output = system_call(SYS_OPEN,argv[j+1],64,0777);
          output = system_call(SYS_OPEN,argv[j+1],1,0777);
      }
      else if(strcmp(argv[j],"-i")==0){
          input = system_call(SYS_OPEN,argv[j+1],0,0777);
      }
      else if(strcmp(argv[j],"-d")==0){
          debug = 1;
      }
  }
  
  int size = system_call(SYS_READ,input,buffer,256);
  int i;
  for(i=0;i<size;i++){
    if (buffer[i] >='A' && buffer[i] <= 'Z')
        buffer[i] += 32;
  }
  write = system_call(SYS_WRITE,output,buffer,size);
  if(debug){
      system_call(SYS_WRITE,STDERR,itoa(SYS_READ),4);
      system_call(SYS_WRITE,STDERR,itoa(size),4);
      system_call(SYS_WRITE,STDERR,"\n",1);
      system_call(SYS_WRITE,STDERR,itoa(SYS_OPEN),4);
      system_call(SYS_WRITE,STDERR,itoa(output),4);
      system_call(SYS_WRITE,STDERR,"\n",1);
      system_call(SYS_WRITE,STDERR,itoa(SYS_OPEN),4);
      system_call(SYS_WRITE,STDERR,itoa(input),4);
      system_call(SYS_WRITE,STDERR,"\n",1);
      system_call(SYS_WRITE,STDERR,itoa(SYS_WRITE),4);
      system_call(SYS_WRITE,STDERR,itoa(write),4);
      system_call(SYS_WRITE,STDERR,"\n",1);
  }
  return 0;
}
