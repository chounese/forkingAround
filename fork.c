#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int fd[2];

// example3.c
//
// The third example in Smashing The Stack For Fun and Profit.
// Showing how to alter the return address through pointer manipulation.
//
// To compile: "gcc -o example3.exe example3.c -fno-stack-protector"

#include <stdio.h>
#include <unistd.h>

/* Read characters from the pipe and echo them to stdout. */

char* read_from_pipe (int file)
{
  FILE *stream;
  int c;
  stream = fdopen (file, "r");
  //while ((c = fgetc (stream)) != EOF)
  //  putchar (c);
  fseek(stream, 0L, SEEK_END);
  int size = ftell(stream);
  rewind(stream);
  char *result = malloc(sizeof(char) * (size+2));
  int i;
  for (i = 0; i < size; i++)
  {
    result[i] = fgetc(stream);
  }
  result[size] = '\0';
  fclose (stream);
  return result;
}

/* Write some random text to the pipe. */

void write_to_pipe (int file, int x)
{
  FILE *stream;
  stream = fdopen (file, "w");
  //fprintf (stream, "hello, world!\n");
  //fprintf (stream, "goodbye, world!\n");
  fprintf(stream,"%d\n", x);
  fclose (stream);
}

void findRA()
{
  close(fd[0]);
  write_to_pipe(fd[1], 725);
  return;
}

/* Forks the process. */

int forker()
{
	int pid, status;

	pipe(fd);

	switch (pid = fork()) {

	case 0: /* child */
		findRA();
		return 0;;

	default: /* parent */
		close(fd[1]);
		int result;	
		sscanf(read_from_pipe(fd[0]), "%d", &result);
		return result;

	case -1:
		perror("fork");
		exit(1);
	}
	exit(0);
}
