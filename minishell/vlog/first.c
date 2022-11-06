#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"
int main(int argc, char **argv)
{
    char *cmd;
    while (1)
    {
        print_prompt1();//프롬포트를 출력하고
        cmd = read_cmd();//명령을 읽습니다.
        if(!cmd)
        {
            exit(EXIT_SUCCESS);
        }
        if(cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
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