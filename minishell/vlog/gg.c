#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
// #include "shell.h"
int main(int argc, char **argv)
{
    char *cmd;
    while (1)
    {
        cmd = readline("jshell$ ");
        if(!cmd)
        {
            exit(EXIT_SUCCESS); //널인경우 성공
        }
        if(cmd[0] == '\0' || ft_strcmp(cmd, "\n") == 0)
        {
            free(cmd);
            continue;
        }
        if(strcmp(cmd, "exit\n") == 0)
        {
            free(cmd);
            break;
        }
        printf("%s\n", cmd);
        free(cmd);
    }
    exit(EXIT_SUCCESS);
} 