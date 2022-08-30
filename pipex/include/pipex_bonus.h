/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:57:04 by joushin           #+#    #+#             */
/*   Updated: 2022/08/30 17:20:08 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>  //open
# include <unistd.h> //close, read, write, dup, dup2,access,
					//exeve,pipe ,fork,unlink
# include <stdlib.h> //malloc, free
# include <stdio.h>  //perror
# include <string.h> //strerror
# include <sys/wait.h> //wait, wait pid
# define BUFFER_SIZE 42

typedef struct s_px
{
	char	**cmd; //명령어 , 옵션들, 널
	char	*cmd_path[2]; //명령어 경로 합쳐서, 널//둘다 널로 초기화 해주기
	int		idx;// 몇번째 파이프인지
	struct s_px	*next;
}t_px ;

typedef struct s_data
{
	char	*infile;//들어온 파일
	char	*outfile;//나갈 파일
	char	**ev;//환경변수들
	char	**path;//환경변수에서 자른 path
	int		**pipefd;//처음에 만든 파이프
	int		pipe_num;
	int		flag;//파이프 보너스 >> << 를 위해서 주는 flag
	t_px	*cmd_node_head;//각 명령어 별로 노드로
	t_px	*cmd_node_tail;
}t_data;

void	print_error(int Flag, char *s);

void	node_init(t_data *px, char **argv);
void	parse_input(t_data *px, int argc, char **argv, char **envp);
void	cmd_init(t_data *px);

void	exec_first(t_data *px);
void	exec_last(t_data *px);
void	exec_pipe(int idx, t_data *px);
int		fork_child(t_data *px);

void	my_free(char **to_free);
char	*ft_mstrdup(const char *s1);
char	*ft_mstrjoin(char const *s1, char const *s2);
t_px	*mlst_find(int idx, t_data *data);
pid_t	mfork(void);

char	**ft_msplit(char const *str, char c);

size_t	ft__strlen(const char *str);
void	*ft__memmove(void *dst, const void *src, size_t len);
size_t	ft__strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft__strdup(const char *s1);
char	*ft__strjoin(char *s1, char *s2);

char	*get_next_line(int fd);

#endif
// fork할 때 pid가 0 : 자식이다.
// pipe함수
// fd[2]에서
// fd[0] : 데이터를 입력 받을 수 있는 파일 디스크립터가 담김 (파이프 출구)
// fd[1] : 함수 호출 후 데이터를 출력할 수 있는 파일 디스크립터가 담긴다.(파이프 입구)
// 자식 프로세스에서 write(fd[1],"쓰고 싶은 글",바이트수);
// read(fd[0],buffer,BUFSIZE);가
// 에러 발생시 에러노의 값을 가져와서 출력 구현하기
