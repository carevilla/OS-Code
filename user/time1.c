/* @author Christian Revilla
 * student ID 80580582
 * returns the number of time ticks the program passed as argument used
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int main(int argc, char **argv)
{
  int start_t, end_t;
  char *argv_list[] = { (char *) NULL };  /* empty arg list */

  /* must have one argument only */
  if(argc != 2){
    fprintf(2, "usage: time1 argument\n");
    exit(1);
  }

  start_t = uptime();   /* start clock */
  int pid = fork();     /* create child */

  /* we are in the child process */
  if ( pid == 0 ) {
    exec(argv[1],argv_list);
    exit(0);
  }
  
  /* in parent but error occured in fork() */
  else if ( pid == -1 ) {
    exit(-1);
  }

  /* in parent waiting for child to finish, compute results */
  wait(&pid);
  end_t = uptime();
  printf("elapsed time: %d ticks\n", (end_t - start_t));

  exit(0);
}
