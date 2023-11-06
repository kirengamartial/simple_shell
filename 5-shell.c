#include "shell.h"

void my_simple_shell(void)
{
    char *command = NULL;
    size_t len = 0;
    ssize_t read_bytes;
    char *path = "/bin:/usr/bin";
    char *token;

    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);
        read_bytes = getline(&command, &len, stdin);
        if (read_bytes == -1)
        {
            perror("getline");
            break;
        }
        if (command[read_bytes - 1] == '\n')
            command[read_bytes - 1] = '\0';

        if (strcmp(command, "env") == 0)
        {
            // Implement the env built-in command
            char **env = environ;
            while (*env)
            {
                write(STDOUT_FILENO, *env, strlen(*env));
                write(STDOUT_FILENO, "\n", 1);
                env++;
            }
        }
        else
        {
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

    if (command)
        free(command);
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
            perror("my_simple_shell");
            _exit(127);
        }
    }
    else if (pid < 0)
    {
        perror("my_simple_shell");
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
