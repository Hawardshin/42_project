/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:07:21 by joushin           #+#    #+#             */
/*   Updated: 2022/08/24 18:51:04 by joushin          ###   ########.fr       */
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

typedef struct s_px
{
	char		**cmd[3];// 명령 모음
	char		**path;// 경로
	char		*cmd_path[3][2];//명령어 경로 모음
	int			pipefd[2];// 파이프 fd 0이 출구 1이 입구
	// int			num;//??
	char		*infile;//입력 파일
	char		*outfile;// 출력 파일
	char		**ev;// 환 경변수 모음
	// char		**exe_path;//명령어 실행 경로
	struct s_px	*prev;//이전
	struct s_px	*next;//다음
}t_px ;

#endif

void	ft_error_check(int idx, t_px *pipex);
void	my_free(char **to_free);
char	*mft_strdup(const char *s1);
void	parse_input(t_px *pipex, char **argv, char **envp);
void	check_cmd(t_px *pipex);
void	level_fuc(t_px *pipex);


// fork할 때 pid가 0 : 자식이다.
// pipe함수
// fd[2]에서
// fd[0] : 데이터를 입력 받을 수 있는 파일 디스크립터가 담김 (파이프 출구)
// fd[1] : 함수 호출 후 데이터를 출력할 수 있는 파일 디스크립터가 담긴다.(파이프 입구)
// 자식 프로세스에서 write(fd[1],"쓰고 싶은 글",바이트수);
// read(fd[0],buffer,BUFSIZE);가
// 에러 발생시 에러노의 값을 가져와서 출력 구현하기
