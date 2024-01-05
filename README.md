# Minishell Allowed Functions

## I have to get familiar with all these new function


| Function | Prototype                                     | Library            |                                    Description |
| ---------------- | ------------------------------------- | -------------------| ---------------------------------------------- |
| readline         | `char *readline(const char *prompt);` | readline/readline.h| Reads a line from the terminal and returns it. |
| rl_clear_history | `void rl_clear_history(void);`        | readline/history.h | Clears the history list by freeing the memory of each element. |
| rl_on_new_line   | `int rl_on_new_line(void);`           | readline/readline.h| Tells the update routines that we have moved onto a new line. |
| rl_replace_line  | `int rl_replace_line(const char *text, int clear_undo);`   | readline/readline.h | Replaces the contents of rl_line_buffer with text. |
| rl_redisplay     | `void rl_redisplay(void);`            | readline/readline.h| Redraws the current line. |
| add_history      | `void add_history(const char *string);`| readline/history.h| Adds string to the history list. |

---
<br>

# Useful function 

| Function | Prototype                                     | Library            |                                    Description |
| ---------------- | ------------------------------------- | -------------------| ---------------------------------------------- |
| access 	         | `int access(const char *pathname, int mode);` 	| unistd.h 	| Checks if the calling process can access the file pathname. |
| getcwd 	         | `char *getcwd(char *buf, size_t size);`| unistd.h 	        |Gets the current working directory.|
| chdir 	         | `int chdir(const char *path);` 	      | unistd.h 	        |Changes the current working directory.|
| stat 	           | `int stat(const char *pathname, struct stat *statbuf);` 	  | sys/stat.h 	|Gets the status of the file pointed to by pathname.|
| lstat 	         | `int lstat(const char *pathname, struct stat *statbuf);` 	| sys/stat.h 	|Like stat(), but if pathname is a symbolic link, then it returns information about the link itself, not the file that it refers to.|
| fstat 	         | `int fstat(int fd, struct stat *statbuf);` | sys/stat.h 	  |Is identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor fd.|
| unlink 	         | `int unlink(const char *pathname);` 	      | unistd.h 	    |Deletes a name from the filesystem.|

---
<br>

# Useful function 

| Function | Prototype                                     | Library            |                                    Description |
| ---------------- | ------------------------------------- | -------------------| ---------------------------------------------- |
| execve 	         | `int execve(const char *filename, char *const argv[], char *const envp[]);` 	| unistd.h 	|Executes the program pointed to by filename. filename must be either a binary executable, or a script starting with a line of the form "#! interpreter [arg]".|
| dup 	           | `int dup(int oldfd);` 	                    | unistd.h 	    |Creates a copy of the file descriptor oldfd.|
| dup2 	           | `int dup2(int oldfd, int newfd);` 	        | unistd.h 	    |Duplicates one file descriptor, making them aliases, and then deleting the old file descriptor. It makes newfd be the copy of oldfd, closing newfd first if necessary.|
| pipe 	           | `int pipe(int pipefd[2]);` 	              | unistd.h 	    |Creates a pipe, a unidirectional data channel that can be used for interprocess communication.|
| opendir 	       | `DIR *opendir(const char *name);` 	        | dirent.h 	    |Opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream. The stream is positioned at the first entry in the directory.|
| readdir 	       | `struct dirent *readdir(DIR *dirp);` 	    | dirent.h 	    |Returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp. It returns NULL on reaching the end of the directory stream or if an error occurred.|
| closedir 	       | `int closedir(DIR *dirp);` 	              | dirent.h 	    |Closes the directory stream associated with dirp. A successful call to closedir() also closes the underlying file descriptor associated with dirp.|
| strerror 	       | `char *strerror(int errnum);` 	            | string.h 	    |Returns a pointer to a string that describes the error code passed in the argument errnum.|
| perror   	       | `void perror(const char *s);`   	          | stdio.h   	  |Prints a descriptive error message to stderr. First (if s is not NULL and *s is not '\0'), the argument string s is printed, followed by a colon and a blank. Then an error message corresponding to the current value of errno and a new-line.|
| isatty   	       | `int isatty(int fd);`   	                  | unistd.h   	  |Tests whether fd is an open file descriptor referring to a terminal.|
| ttyname  	       | `char *ttyname(int fd);`   	              | unistd.h   	  |Returns a pointer to a string which is the null-terminated filename of the terminal associated with fd (i.e., its pathname in /dev).|

---
<br>

# Function used in get_next_line and other projects

## I won't go too much into details for those function since we already used them in our 42 project 

| Function | Prototype | Library | des   | 
| ---------| --------- | ------- |-------|
| ``printf`` | `int printf(const char *format, ...);` | stdio.h | Prints formatted output to stdout. |
| ``malloc`` | `void* malloc(size_t size);` | stdlib.h | Allocates size bytes of uninitialized storage. |
| ``free`` | `void free(void* ptr);` | stdlib.h | Deallocates the memory space pointed to by ptr. |
| ``write`` | `ssize_t write(int fd, const void *buf, size_t count);` | unistd.h | Writes up to count bytes from the buffer pointed buf to the file referred to by the file descriptor fd. |
| ``open`` 	| `int open(const char *pathname, int flags); int open(const char *pathname, int flags, mode_t mode);` 	| fcntl.h 	| Opens the file specified by pathname. |
| ``read`` 	| `ssize_t read(int fd, void *buf, size_t count);` 	| unistd.h 	| Reads up to count bytes from file descriptor fd into the buffer starting at buf. |
| ``close`` 	| `int close(int fd);` 	| unistd.h 	| Closes a file descriptor. |

---
<br>

# Function used in pipex and Philospher Bonus 
## I wish I had enough time to push my philosopher with them Bonus done, but unluckly I needed to hurry up. For this reason most of those function are new to me.
| Function | Prototype | Library | Description |
| --- | --- | --- | --- |
| fork 	| `pid_t fork(void);` 	| unistd.h 	|Creates a new process by duplicating the existing process. The new process is called a child process.|
| wait 	| `pid_t wait(int *wstatus);` 	| sys/wait.h 	|Suspends the calling process until one of its child processes terminates.|
| waitpid 	| `pid_t waitpid(pid_t pid, int *wstatus, int options);` 	| sys/wait.h 	| Suspends the calling process until a specific child process terminates.|
| wait3 	| `pid_t wait3(int *wstatus, int options, struct rusage *rusage);` 	| sys/wait.h and sys/resource.h 	| Suspends the calling process until a child process terminates while also providing resource usage information about the child.|
| wait4 	| `pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);` 	| sys/wait.h and sys/resource.h 	| Suspends the calling process until a specific child process terminates while also providing resource usage information about the child.|

---
<br>

# Function used in Minitalks 
## I won't go too much into details for those function since we already used them in our 42 project 

| Function | Prototype | Library | Description |
| --- | --- | --- | --- |
| ``signal`` 	| `typedef void (*sighandler_t)(int); sighandler_t signal(int signum, sighandler_t handler);` 	| signal.h 	| Sets a function to handle signal i.e., a signal handler with signal number signum.|
| ``sigaction`` 	| `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);` 	| signal.h 	| Allows to choose one of three ways in which receipt of the signal number signum is to be subsequently handled. If act is non-NULL, it specifies this choice; if it is NULL then the choice is not changed but any existing setting can be examined by storing it in oldact.|
| ``sigemptyset`` 	| `int sigemptyset(sigset_t *set);` 	| signal.h 	|Initializes set to be empty.|
| ``sigaddset``  	    | `int sigaddset(sigset_t *set, int signum);` 	    | signal.h 	    |Adds signum from set.|
| ``kill`` 	            | `int kill(pid_t pid, int sig);` 	                | signal.h 	    |Sends a signal to a process or a group of processes.|
| ``exit`` 	            | `void exit(int status);` 	                        | stdlib.h 	    |Causes normal process termination and the value of status & 0377 is returned to the parent.|








| Day    | Task Description                                      | Resources |
| ------ | ----------------------------------------------------- | --------- |
| day one | the quotes goes like this | day one | 
