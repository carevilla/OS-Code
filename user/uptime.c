/* @author Christian Revilla
 * student ID 80580582
 * Here is the homework 1 code for uptime
 * When uptime is called prints the number of clock ticks defined by xv6 kernal
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
  int n;
  n = uptime();

  printf("up %d clock ticks\n", n );

  exit(0);

}
