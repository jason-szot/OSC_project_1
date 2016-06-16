#include <unistd.h>		// to use system calls:  pid_t fork(void) int execve(const char*, char *const argv[], char *const envp[])
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFSZ 256

int main(int argc, char **argv)
{
	
	if (argc <= 1){	// need to pass an argument string to pass from child to parent for part 1
		printf("Usage is: project1 <text to pass>\n");
		perror("missing argument");
		exit(EXIT_FAILURE);
	}

	int cow = 10;	// as per instructions, to demonstrate copy-on-write
	char *buffer = malloc(BUFSZ*sizeof(char));
	int pfd[2];
	int pid;
	pipe(pfd);

	// error checking
	if (pipe(pfd) < 0){
		/* Prefix the error messages related to pipe system call with "pipe:" */
		perror("pipe");
		exit(EXIT_FAILURE); /* Need to include stdlib.h for EXIT_FAILURE */
	}

	pid = fork();

	// error checking
	if(pid < 0){
		// error creating fork
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	if (pid ==0){ // child process
		// display value of variable cow
		printf("child value of cow is %d\n",cow);
		printf("child writes %s to pipe.\n", argv[1]);
		write(pfd[1], argv[1], 9);	// write a message from child to pipe
		printf("child changes value of cow\n");
		cow = 1000;	// change value of cow to 1000 in one process
		printf("child value of cow is %d\n",cow);	// display value of cow in both processes to see they are different
	}
	else{	// parent process
		// display value of variable cow
		printf("parent value of cow is %d\n",cow);
		wait(0);
		read(pfd[0], buffer, BUFSZ);
		printf("parent reads %s from pipe.\n", buffer);
		printf("parent value of cow is %d\n",cow);	// verify they are different

	}

	return EXIT_SUCCESS;
}