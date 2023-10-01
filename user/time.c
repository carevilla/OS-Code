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
  int start_t, end_t, elapsed_t, pid;
  char *argv_list[] = { (char *) NULL, (char *) NULL, (char *) NULL };  /* empty arg list */
  struct rusage r;

  /* must have at least 2 and no more than 3 argument only */
  if(argc < 2){
    fprintf(2, "usage: time <cmd> [cmd_argument]\n");
    exit(1);
  }

  for (int i=0; i<argc; ++i ) argv_list[i] = argv[i+1];
  //for (int i=0; argv[i] != (char *) NULL; ++i )
  //  fprintf(2, "argv[%d] = %s\n", i, argv_list[i]);
  
  start_t = uptime();
  pid = fork();
  if ( pid == 0 ) {
    exec(argv[1],argv_list);
    exit(0);
  }
  
  /* in parent waiting for child to finish, compute results */
  wait2(&pid,&r);
  end_t = uptime();
  elapsed_t = end_t-start_t;
  printf("elapsed time: %d ticks, cputime: %d ticks, %d\% CPU\n", elapsed_t, r.cputime, (int) (100.0*r.cputime/elapsed_t));
  exit(0);
}
