#include "shell.h"

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

    return (0);
}
