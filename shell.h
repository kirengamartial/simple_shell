#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

void execute_command(char *command);
void minishell(void);
void myshell(void);
void my_new_shell(void);
void execute_command(char *command, char *path);
void my_better_shell(void);
void execute_command(char *command, char *path);
void split_and_execute(char *command, char *path);
void my_simple_shell(void);
void execute_command(char *command, char *path);

#endif /* SHELL_H */
