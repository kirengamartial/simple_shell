#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line(void);
char **tokenize(char *input);
int execute(char **args);

#endif /* SHELL_H */
