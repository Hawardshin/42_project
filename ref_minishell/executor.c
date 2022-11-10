/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:17:12 by joushin           #+#    #+#             */
/*   Updated: 2022/11/07 20:37:50 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "./include/shell.h"
#include "./include/node.h"
#include "./include/executor.h"
//search_path()나열된 디렉토리를 검색하여 명령의 실행 파일을 찾습니다.
//즉 환경변수 검색해서 찾아오는 것입니당. 
//각 디렉토리에 대해 디렉토리 이름에 명령 이름을 추가하여 경로 이름을 만든 다음 지정된 경로 이름으로 파일이 존재하는지 확인하기 위해 호출합니다
//단 실행권한은 무조건 있다고 보는게 이건데 실행권한이 없는경우는?
//모든 디렉토리를 검색하여 명령을 찾는 데 실패하면 $PATH반환 NULL 
//이건 pipex코드 그대로 사용해야겠네요 함수 변경 예정.
char    *search_path(char *file)
{
    char *PATH = getenv("PATH");
    char *p    = PATH;
    char *p2;
    
    while(p && *p)
    {
        p2 = p;
        while(*p2 && *p2 != ':')
        {
            p2++;
        }
        
	int  plen = p2-p;
        if(!plen)
        {
            plen = 1;
        }
        
        int  alen = strlen(file);
        char path[plen+1+alen+1];
        
	strncpy(path, p, p2-p);
        path[p2-p] = '\0';
        
	if(p2[-1] != '/')
        {
            strcat(path, "/");
        }
        strcat(path, file);
        
	struct stat st;
        if(stat(path, &st) == 0)
        {
            if(!S_ISREG(st.st_mode))
            {
                errno = ENOENT;
                p = p2;
                if(*p2 == ':')
                {
                    p++;
                }
                continue;
            }
            p = malloc(strlen(path)+1);
            if(!p)
            {
                return NULL;
            }
            
	    strcpy(p, path);
            return p;
        }
        else    /* file not found */
        {
            p = p2;
            if(*p2 == ':')
            {
                p++;
            }
        }
    }
    errno = ENOENT;
    return NULL;
}
//시작이 /이면 그냥 명령이라고 생각하고 실행을 하고 아니면 명령을 찾을 다음에 
int do_exec_cmd(int argc, char **argv)
{
    (void) argc;
    if(strchr(argv[0], '/'))
    {
        execv(argv[0], argv);
    }
    else
    {
        char *path = search_path(argv[0]);
        if(!path)
        {
            return 0;
        }
        execv(path, argv);
        free(path);
    }
    return 0;
}
//마지막으로 실행된 명령의 인수 목록을 저장하는 데 사용한 메모리를 해제합니다.
static inline void free_argv(int argc, char **argv)
{
    if(!argc)
    {
        return;
    }
    while(argc--)
    {
        free(argv[argc]);
    }
}
//명령의 AST를 가져와 인수 목록으로 변환합니다(argv[0]에는 실행하려는 명령의 이름이 포함되어 있음을 기억하십시오).
//그런 다음 함수는 새 자식 프로세스를 분기하고 자식 프로세스에서는 do_exec_cmd를 실행해서 이건 pipex와 같네요 ㅎㅎ
int do_simple_command(struct node_s *node)
{
    if(!node)
    {
        return 0;
    }
    struct node_s *child = node->first_child;
    if(!child)
    {
        return 0;
    }
    
    int argc = 0;
    long max_args = 255;
    char *argv[max_args+1];/* keep 1 for the terminating NULL arg */
    char *str;
    
    while(child)
    {
        str = child->val.str;
        argv[argc] = malloc(strlen(str)+1);
        printf("%s\n",str);
	if(!argv[argc])
        {
            free_argv(argc, argv);
            return 0;
        }
        
	strcpy(argv[argc], str);
        if(++argc >= max_args)
        {
            break;
        }
        child = child->next_sibling;
    }
    argv[argc] = NULL;
    pid_t child_pid = 0;
    printf("%s\n%s\n",argv[0],argv[1]);
    if ((child_pid = fork()) == 0)
    {
        do_exec_cmd(argc, argv);
        fprintf(stderr, "error: failed to execute command: %s\n", 
                strerror(errno));
        if(errno == ENOEXEC)
        {
            exit(126);
        }
        else if(errno == ENOENT)
        {
            exit(127);
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }
    else if(child_pid < 0)
    {
        fprintf(stderr, "error: failed to fork command: %s\n", 
                strerror(errno));
        return 0;
    }
    int status = 0;
    waitpid(child_pid, &status, 0);
    free_argv(argc, argv);
    
    return 1;
}