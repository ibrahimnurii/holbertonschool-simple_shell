#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> /* wait function declaration */

/**
 * main - Simple UNIX command line interpreter
 *
 * Description: This function creates a basic shell that accepts one-word
 * commands, handles execution, and displays errors if the command fails.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *args[2];

    while (1)
    {
        /* Display prompt */
        write(STDOUT_FILENO, "#cisfun$ ", 9);

        /* Read user input */
        read = getline(&line, &len, stdin);
        if (read == -1) /* Handle EOF (Ctrl+D) */
        {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        /* Remove newline character */
        line[read - 1] = '\0';

        /* Prepare arguments */
        args[0] = line; /* Command */
        args[1] = NULL; /* NULL-terminated for execve */

        /* Execute command */
        if (fork() == 0) /* Child process */
        {
            execve(args[0], args, NULL);
            perror("./shell"); /* If execve fails */
            exit(EXIT_FAILURE);
        }
        else /* Parent process */
        {
            wait(NULL); /* Wait for child process to finish */
        }
    }

    free(line); /* Free allocated memory */
    return (0);
}

