/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:07:21 by joushin           #+#    #+#             */
/*   Updated: 2022/08/25 16:57:13 by joushin          ###   ########.fr       */
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
	char	**cmd; //명령어 , 옵션들, 널
	char	*cmd_path[2]; //명령어 경로 합쳐서, 널//둘다 널로 초기화 해주기
	int		idx;// 몇번째 파이프인지
	struct s_px *bef;
	struct s_px	*next;
}t_px ;

typedef struct s_data
{
	char	*infile;//들어온 파일
	char	*outfile;//나갈 파일
	char	**ev;//환경변수들
	char	**path;//환경변수에서 자른 path
	int		pipefd[2];//처음에 만든 파이프
	int		pipe_num;
	t_px	*cmd_node_head;//각 명령어 별로 노드로
	t_px	*cmd_node_tail;
}t_data;

void	ft_error_check(int idx, t_px *pipex);
void	my_free(char **to_free);
char	*mft_strdup(const char *s1);
void	parse_input(t_data *px, char **argv, char **envp);
void	check_cmd(t_px *pipex);
void	level_fuc(t_px *pipex);
void	print_error(int	Flag, char *s);
char	**ft_msplit(char const *str, char c);
#endif
// fork할 때 pid가 0 : 자식이다.
// pipe함수
// fd[2]에서
// fd[0] : 데이터를 입력 받을 수 있는 파일 디스크립터가 담김 (파이프 출구)
// fd[1] : 함수 호출 후 데이터를 출력할 수 있는 파일 디스크립터가 담긴다.(파이프 입구)
// 자식 프로세스에서 write(fd[1],"쓰고 싶은 글",바이트수);
// read(fd[0],buffer,BUFSIZE);가
// 에러 발생시 에러노의 값을 가져와서 출력 구현하기
