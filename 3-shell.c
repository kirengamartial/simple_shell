#include "shell.h"

void my_new_shell(void)
{
    char command[1024];
    ssize_t read_bytes;
    char *path = "/bin:/usr/bin";
    char *token;

    while (1)
    {
        write(STDOUT_FILENO, ":) ", 3);
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

            token = strtok(path, ":");
            while (token != NULL)
            {
                if (access(token, X_OK) == 0)
                {
                    execute_command(command, token);
                    break;
                }
                token = strtok(NULL, ":");
            }

            if (token == NULL)
                write(STDOUT_FILENO, "Command not found\n", 19);
        }
    }
}

void execute_command(char *command, char *path)
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
        if (execve(path, args, NULL) == -1)
        {
            perror("my_new_shell");
            _exit(127);
        }
    }
    else if (pid < 0)
    {
        perror("my_new_shell");
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
