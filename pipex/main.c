/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:23 by joushin           #+#    #+#             */
/*   Updated: 2022/08/19 22:00:53 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

#define BUFSIZE 30
/*pipe함수 첫번째 예제*/
// int main()
// {
//     int fd[2];
//     char buff[BUFSIZE];
//     pid_t   pid;
//     int state;

//     state = pipe(fd);
//     if (state == -1)
//     {
//         puts("pipe_error");
//         exit(1);
//     }
//     pid = fork();

//     if (pid == -1)
//     {
//         puts("fork error");
//         exit(1);
//     }
//     else if (pid == 0)
//     {
//         write(fd[1], "연결성공 \n",30);
//     }
//     else
//     {
//         read(fd[0],buff,BUFSIZE);
//         printf("%s",buff);
//         // write (1, buff,BUFSIZE);
//     }
//     return (0);
// }


// int main(int argc, char *argv[])
// {
//     int fd[2];
//     char buffer[BUFSIZE];
//     pid_t pid;
//     int state;

//     state = pipe(fd);
//     if (state == -1)
//     {
//         puts("pipeerror");
//         exit(1);
//     }
//     pid = fork();
//     if (pid == -1)
//     {
//         puts("fork() error");
//         exit(1);
//     }
//     else if (pid == 0)
//     {
//         write(fd[1], "연결 성공!! \n", 25);
//         // sleep(2);
//         read(fd[0],buffer,BUFSIZE);
//         printf("in child process : %s\n\n",buffer);
//     }
//     else
//     {
//         read(fd[0], buffer,BUFSIZE);
//         printf("in parent process : %s\n\n",buffer);
//         write(fd[1],"정말 좋아!!",25);
//         // sleep(2);
//     }
// }

int main(int argc, char *argv[])
{
    int fd1[2],fd2[2];
    char buffer[BUFSIZE];
    pid_t pid;

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        puts("pipe() error");
        exit(1);
    }
    else if (pid == 0)
    {
        write(fd[1], "연결 성공 !!!\n",25);
        read(fd2[0])
    }
}
