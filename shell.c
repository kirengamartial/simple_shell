#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_TOKENS 64

char **tokenize(char *input)
{
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (tokens == NULL)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(input, " \t\n");  // Tokenize by space, tab, and newline
    int i = 0;

    while (token != NULL)
    {
        tokens[i] = strdup(token);
        if (tokens[i] == NULL)
        {
            perror("strdup failed");
            exit(EXIT_FAILURE);
        }
        i++;

        token = strtok(NULL, " \t\n");
    }

    tokens[i] = NULL;  // Null-terminate the array

    return tokens;
}

int execute(char **args)
{
    if (args[0] == NULL)
    {
        return 0;  // No command provided
    }

    if (strcmp(args[0], "exit") == 0)
    {
        return 1;  // Exit the shell
    }

    // Execute external commands
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        // Child process
        if (execve(args[0], args, NULL) == -1)
        {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork failed");
    }
    else
    {
        // Parent process
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 0;  // Continue with the shell
}

int main(void)
{
    char *input;
    char **tokens;
    int status;

    while (1)
    {
        printf("$ ");  // Print a shell prompt
        input = read_line();  // Read user input

        tokens = tokenize(input);  // Tokenize the input

        if (tokens[0] == NULL)
        {
            free(input);
            free(tokens);
            continue;  // If no command, get the next input
        }

        status = execute(tokens);  // Execute the command

        free(input);
        free(tokens);

        if (status == 1)
            break;  // Exit the shell if the command was 'exit'
    }

    return 0;
}
