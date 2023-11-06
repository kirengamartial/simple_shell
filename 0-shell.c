#include "shell.h"

void execute_command(char *command)
{
    int i = 0; 
    char *args[64];
    char *token;
    int status;

    token = strtok(command, " \n");
    for (int i = 0; token != NULL; i++)
    {
        args[i] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;

    pid_t pid = fork();

    if (pid == 0)
    {
        if (execve(args[0], args, NULL) == -1)
        {
            perror("shell");
            _exit(127);
        }
    }
    else if (pid < 0)
    {
        perror("shell");
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
