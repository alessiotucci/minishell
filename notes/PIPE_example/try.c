void piping(t_list_of_tok *current, t_type_of_tok type)
{
	int p[2]; // create a pipe
	char *command = current->command_as_string; // get the command from the node
	char **args = current->command_as_array; // get the arguments from the node
	char **envp = NULL; // get the environment variables from somewhere
	pid_t pid;

	if (pipe(p) < 0) // initialize the pipe
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	// redirect stdout to write end of pipe
	if (dup2(p[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(p[0]);
		close(p[1]);
		exit(EXIT_FAILURE);
	}
	close(p[0]); // close read end of pipe
	pid = fork(); // fork a child process
	if (pid < 0)
	{
		perror("fork");
		close(p[1]);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) // in the child process
	{
		// redirect stdin to read end of pipe
		if (dup2(p[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(p[0]);
			close(p[1]);
			exit(EXIT_FAILURE);
		}
		close(p[1]); // close write end of pipe
		// execute the command
		execve(command, args, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else // in the parent process
	{
		close(p[0]); // close read end of pipe
		close(p[1]); // close write end of pipe
		wait(NULL); // wait for the child process to finish
	}
}

