#include "shell.h"

void myshell(void)
{
    char command[1024];
    ssize_t read_bytes;

    while (1)
    {
        write(STDOUT_FILENO, "#cisfun$ ", 9);
        read_bytes = read(STDIN_FILENO, command, sizeof(command));
        if (read_bytes == 0)
        {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        if (read_bytes == -1)
            perror("read");
        else
        {
            command[read_bytes] = '\0';
            if (command[read_bytes - 1] == '\n')
                command[read_bytes - 1] = '\0';
            execute_command(command);
        }
    }
}

void execute_command(char *command)
{
    char *args[64];
    char *token;
    int status;
    int i = 0;

    token = strtok(command, " \n");
    while (token != NULL)
    {
        args[i] = token;
        token = strtok(NULL, " \n");
        i++;
    }
    args[i] = NULL;

    pid_t pid = fork();

    if (pid == 0)
    {
        if (execve(args[0], args, NULL) == -1)
        {
            perror("myshell");
            _exit(127);
        }
    }
    else if (pid < 0)
    {
        perror("myshell");
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
