#include "shell.h"

void minishell(void)
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
    (void)command;
    write(STDOUT_FILENO, "./minishell: No such file or directory\n", 43);
}
