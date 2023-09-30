/* @author Christian Revilla
 * student ID 80580582
 * returns the number of time ticks the program passed as argument used
 */

#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/pstat.h"
#include "user/user.h"
#include <stddef.h>

int main(int argc, char **argv)
{
  int start_t = 0, end_t, pid;
  char *argv_list[] = { (char *) NULL };  /* empty arg list */
  struct rusage r;
  r.cputime = 1;

  /* must have at least 2 and no more than 3 argument only */
  if(argc < 2){
    fprintf(2, "usage: time argument\n");
    exit(1);
  }

  if(argc == 2){

    start_t = uptime();   /* start clock */
    pid = fork();     /* create child */

    /* we are in the child process */
    if ( pid == 0 ) {
      exec(argv[1],argv_list);
      exit(0);
    }
  
    /* in parent but error occured in fork() */
    else if ( pid == -1 ) {
      exit(-1);
    }
  }

  if(argc == 3){

    start_t = uptime();
    pid = fork();

    if(pid == 0){
      exec(argv[1],argv_list);
      exit(0);
    }
    else if (pid == -1){
      exit(-1);
    }
  }

  /* in parent waiting for child to finish, compute results */
  wait2(&pid,&r);
  end_t = uptime();
  printf("elapsed time: %d ticks\n", (end_t - start_t));
  printf("CPU time: %d\n" , r.cputime);
  exit(0);
}
