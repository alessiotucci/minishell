#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

int main(int ac, char **av)
{
	int fd[2];
	pid_t pid;
	// Check if the correct arguments are passed.
	if (ac != 3 || strcmp(av[1], ">>") != 0)
	{
		fprintf(stderr, "Usage: %s >> worddelimiter\n", av[0]);
		return 1;
	}
	char *worddelimiter = av[2];
	// Create the pipe.
	if (pipe(fd) == -1)
	{
		fprintf(stderr, "Pipe failed");
		return 1;
	}
	// Fork a child process.
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Fork failed");
		return 1;
	}
	if (pid > 0)
	{
		char read_msg[100];
		// Close the unused end of the pipe.
		close(fd[WRITE_END]);
		// Read from the pipe.
		while (read(fd[READ_END], read_msg, sizeof(read_msg)) > 0)
		{
			if (strcmp(read_msg, worddelimiter) == 0)
				break;
			printf("read: %s\n", read_msg);
		}
		// Close the read end of the pipe.
		close(fd[READ_END]);
	}
	else
	{
		// Child process.
		char write_msg[100];
		// Close the unused end of the pipe.
		close(fd[READ_END]);
		// Write to the pipe.
		while (fgets(write_msg, sizeof(write_msg), stdin) != NULL)
			write(fd[WRITE_END], write_msg, strlen(write_msg));
		// Close the write end of the pipe.
		close(fd[WRITE_END]);
	}
	return 0;
}



