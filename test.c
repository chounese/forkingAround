#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "fork.h"

void writer(int file, int toWrite)
{
  write_to_pipe(file, toWrite + 2);
}

int main(int argc, char **argv)
{
  int output;
  output = forker();  
  printf("%d\n", output);
}
