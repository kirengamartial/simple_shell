#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *command);
void minishell(void);
void myshell(void);
void my_new_shell(void);
void execute_command(char *command, char *path);

#endif /* SHELL_H */
