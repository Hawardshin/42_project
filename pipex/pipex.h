/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:07:21 by joushin           #+#    #+#             */
/*   Updated: 2022/08/19 21:03:12 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>  //open
# include <unistd.h> //close, read, write, dup, dup2,access,
					//exeve,pipe ,fork,unlink
# include <stdlib.h> //malloc, free
# include <stdio.h>  //perror
# include <string.h> //strerror
# include <sys/wait.h> //wait, wait pid
#endif

// fork할 때 pid가 0 : 자식이다.
//pipe함수
// fd[2]에서
// fd[0] : 데이터를 입력 받을 수 있는 파일 디스크립터가 담김 (파이프 출구)
// fd[1] : 함수 호출 후 데이터를 출력할 수 있는 파일 디스크립터가 담긴다.(파이프 입구)
// 자식 프로세스에서 write(fd[1],"쓰고 싶은 글",바이트수);
// read(fd[0],buffer,BUFSIZE);가
