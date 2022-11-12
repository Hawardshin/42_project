/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:34:09 by joushin           #+#    #+#             */
/*   Updated: 2022/11/12 15:58:53 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
#define NODE_H
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

#define IO_TOK 10
#define ARGV_TOK 20
#define PIPE_TOK 30
#define SPACE_TOK 40
#define EOF_TOK 50
#define MAIN_TOK 60

void	print_error(int Flag, char *s);

typedef struct	s_readline
{
	char	*buffer;/* 입력 텍스트 */
	int		bufsize;/* 입력 텍스트 크기*/
	int		now_pos;/* 소스 안에서 문자위치*/
} t_readline;

typedef struct	s_token
{
	int				tok_type;// I/O_red_token ,argv_token, pipeline_token , space_token
	int				text_len;
	char			*text;
	// int				eof; //마지막 토큰인지 확인. 마지막이면 1로 지정해주기.
	struct s_token	*bef;
	struct s_token	*next;
} t_token;

typedef struct	s_main_token
{
	t_token	*start_token;
	t_token	*end_token;
	int		token_num;
} t_main_token ;

typedef struct	s_node
{
	int				idx;	//몇번 째 노드인지
	int				type;	//
							//2개는 명령인 경우만 채워지고 아닌경우 NULL로 채워짐
	char			**argv;	// 명령어 이차원 배열인 이유는 execve를 하기 위해 1번에 명령어와 그 뒤에 인자들.
	char			*cmd_path[2];	//이것도 명령어 경로
	char			*file;//이건 파일로 생겼고 아닌경우 NULL로 채워짐.
	struct s_node	*next;
} t_node;

typedef struct s_main_node
{
	char	**ev;
	char	**path;
	int		**pipefd; //파이프 0 1 두개의 2차원 배열
	int		cmd_num; //명령의 노드의 총 갯수 - 파이프의 갯수로 생각
	t_node	*node_head;
	t_node	*node_tail;
} t_main_node;

#endif
