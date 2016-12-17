#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

//Global pipe variable
int fd[2];

/* Read characters from the pipe and return them in a char array. */

char* read_from_pipe (int file)
{
  FILE *stream;
  int c;
  stream = fdopen (file, "r");
  //allocate space for pipe output
  char *result = (char *)malloc(sizeof(char) * (80));
  int index = 0;
  //read from pipe
  while ((c = fgetc (stream)) != EOF)
    result[index++] = c;
  //add end character
  result[index] = '\0';
  fclose (stream);
  return result;
}

/* Write given input to the pipe. */

void write_to_pipe (int file, int x)
{
  FILE *stream;
  stream = fdopen (file, "w");
  fprintf(stream,"%d", x);
  fclose (stream);
}

void findRA()
{
  close(fd[0]);
  //tests to make sure write_to_pipe is global so that it can be used in RA finding code
  //write some random number as simulation for RA returned
  writer(fd[1], 725);
  return;
}

/* Forks the process. */

int forker()
{
	int pid, status;
	//create a pipe out of fd array
	//index 0 is read index 1 is write
	pipe(fd);

	switch (pid = fork()) {

	case 0: /* child */
		findRA();
		//return something so code can finish running
		return 0;

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
