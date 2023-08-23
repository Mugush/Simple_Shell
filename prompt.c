#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Simple UNIX Command Line Interpreter (Shell)
 *
 * This program provides a basic shell that allows users to input commands.
 * The entered command is executed as a child process using the execlp function.
 * The program supports basic error handling and Ctrl+D (EOF) for exit.
 *
 * Allowed functions and system calls:
 * - access, chdir, close, execve, exit, _exit, fflush, fork, free,
 *   getcwd, getline, getpid, isatty, kill, malloc, open, read, wait, waitpid, write
 */

int main(void)
{
    char input[200];
    char prompt[] = "Simple_Shell> ";

    while (1)
    {
        printf("%s", prompt);

        
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\n");
            break; 
        }

        input[strcspn(input, "\n")] = '\0';

        pid_t pid = fork();

        if (pid == 0)
        {
            execlp(input, input, NULL);
            perror("exec error");
            exit(1);
        }
        else if (pid > 0)
        {
            wait(NULL);
        }
        else
	{
            perror("fork error");
            exit(1);
        }
    }

    return 0;
}
