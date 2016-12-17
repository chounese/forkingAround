#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "fork.h"

int main(int argc, char **argv)
{
  int output;
  output = forker();  
  printf("%d\n", output);
}
