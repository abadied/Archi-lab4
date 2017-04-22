#include "util.h"
#include <dirent.h>
#define SYS_WRITE 4
#define SYS_READ 3 
#define SYS_OPEN 5
#define STDOUT 1
#define STDIN 0
#define STDERR 2
#define SYS_EXIT 1
#define SYS_CLOSE 6

typedef struct ent{
    int inode;
    int offset;
    short len;
    char buf[1];
    
}ent;

int main (int argc , char* argv[], char* envp[])
{
  
  char buffer[2000];
  int debug = 0;
  int input = STDIN; 
  int output = STDOUT;
  int fd,j;
  int count = 0;
  int i = 0;
  char type_arg;
  int suffix = 0;
  ent* entd = buffer;
  for(j=1;j<argc;j++){
      if(strcmp(argv[j],"-d")==0){
          debug = 1;
      }
      else if (strcmp(argv[j],"-s")==0){
          type_arg = argv[j + 1][0];
          suffix = 1;
      }
  }
  fd = system_call(SYS_OPEN,".",0,0777);
  
  count = system_call(141,fd,buffer,200);
  system_call(SYS_WRITE,output,itoa(count),4);
  system_call(SYS_WRITE,output,"\n",1);
  
  while(count>28){
    entd = buffer + i ;
    int length = 0;
    while(entd->buf[length]!=0)
        length = length + 1;

    if(!suffix || entd->buf[length-1]==type_arg){
        system_call(SYS_WRITE,output,"file name:",11);
        system_call(SYS_WRITE,output,entd->buf,10);
        system_call(SYS_WRITE,output,"\n",1);
    }

    if(debug &&(!suffix||entd->buf[length-1]==type_arg)){
        system_call(SYS_WRITE,output,"file length:",13);
        system_call(SYS_WRITE,output,itoa(entd->len) ,2);
        system_call(SYS_WRITE,output,"\n",1);
    }
    count = count-20;
    i = i + 20;
  }
  int closed = system_call(SYS_CLOSE,fd);
  if(fd<0||closed<0)
      system_call(SYS_EXIT,55,1,1);
  
  if(debug){
      system_call(SYS_WRITE,STDERR,"system op:",10);
      system_call(SYS_WRITE,STDERR,itoa(SYS_OPEN),4);
      system_call(SYS_WRITE,output,"\n",1);
      system_call(SYS_WRITE,output,"system result:",14);
      system_call(SYS_WRITE,STDERR,itoa(fd),4);
      system_call(SYS_WRITE,STDERR,"\n",1);
      system_call(SYS_WRITE,STDERR,"system op:",10);
      system_call(SYS_WRITE,STDERR,itoa(SYS_CLOSE),4);
      system_call(SYS_WRITE,output,"\n",1);
      system_call(SYS_WRITE,output,"system result:",14);
      system_call(SYS_WRITE,STDERR,itoa(close),4);
      system_call(SYS_WRITE,STDERR,"\n",1);
  }
  return 0;
}
