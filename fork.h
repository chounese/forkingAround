#ifndef __FORK_H__
#define __FORK_H__

extern void write_to_pipe(int file, int x);
extern int forker();

extern int fd[2];

#endif