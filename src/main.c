//#include "mio_buf.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <signal.h>


void handler(int sig){
      printf("signal is =%d\n",sig);
      return;
}

//typedef  void  (*__sighandler_t)(int );

__sighandler_t _signal(int sig,__sighandler_t handler);

__sighandle_t  signal(int sig,__sighandler_t handler){
      struct sigaction act,oldact;
      act.sa_flags=SA_RESTART;
      act.sa_handler=handler;
      sigemptyset(&act.sa_mask);
      if(sigacton(sig,&act,&oldact)<0){
          return SIG_ERR;
      }
      return &oldact.sa_handler;
}

/*@ main start@*/
int main(int argc,char **argv){
    
         
  // int fd=open("readme.md",O_RDONLY);
    
  _signal(SIGINT,handler);
     
    
    pause();
    return 0;
}
/*@ end end@*/