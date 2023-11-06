#include "shell.h"

int main(void)
{
    char command[1024];

    while (1)
    {
        printf("$ ");
        fgets(command, sizeof(command), stdin);
        execute_command(command);
    }

    return (0);
}
