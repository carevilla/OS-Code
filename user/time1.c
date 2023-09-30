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
  int start_t = 0, end_t, pid;
  char *argv_list[] = { (char *) NULL, (char *) NULL, (char *) NULL };  /* empty arg list */

  /* must have one argument or no more than 3 */
  if((argc < 2) | (argc > 4)){
    printf("usage: time1 <cmd> [paramters]\n");
    exit(1);
  }

  /* enters here if only two arguments are given */
  if(argc == 2){
    start_t = uptime();   /* start clock */
    pid = fork();         /* create child */

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

  /* enters here if 3 arguments were passed .. ex: "time1 sleep 10" */
  if(argc == 3){
    start_t = uptime();
    pid = fork();
    

    /* prep the arg list for exec system call in child */
    if(pid == 0){
      argv_list[0] = argv[1];
      argv_list[1] = argv[2];
      exec(argv[1],argv_list);
      exit(0);
    }
    /* error in parent with fork(); */
    else if( pid == -1){
      exit(-1);
    }
  }

  /* in parent waiting for child to finish, compute results */
  wait(&pid);
  end_t = uptime();
  printf("elapsed time: %d ticks\n", (end_t - start_t));
  exit(0);
}
