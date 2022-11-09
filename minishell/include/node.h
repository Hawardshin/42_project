/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:34:09 by joushin           #+#    #+#             */
/*   Updated: 2022/11/09 22:05:58 by joushin          ###   ########.fr       */
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

void	print_error(int Flag, char *s);

typedef struct s_readline
{
	char	*buffer;/* 입력 텍스트 */
	int		bufsize;/* 입력 텍스트 크기*/
	int		now_pos;/* 소스 안에서 문자위치 ,다시 돌아갈 일이 많으니까*/
	int		done_pos;/*이미 토큰화가 끝난 위치*/
} t_readline;

typedef struct s_node
{
	int				idx;	//몇번 째 노드인지
	int				type;	//명령인지 파일인지 확인. 0이면 파일 1이면 명령
							//2개는 명령인 경우만 채워지고 아닌경우 NULL로 채워짐
	char			**cmd;	// 명령어 이차원 배열인 이유는 execve를 하기 위해
	char			*cmd_path[2];	//이것도 명령어 경로
	char			*file;//이건 파일로 생겼고 아닌경우 NULL로 채워짐.
	struct s_node	*next;
} t_node;

// typedef struct s_tok_buffer
// {
// 	char	*tok_buf;
// 	int		tok_bufsize;
// 	int		tok_bufindex;
// } t_tok_buffer;

typedef struct  s_token
{
	// t_readline	*src;//이거 왜 있지?
	int			text_len;
	char		*text;
	int			eof; //마지막 토큰인지 확인. 마지막이면 1로 지정해주기.
} t_token;

typedef struct s_main_node
{
	char	**ev;
	char	**path;
	int		**pipefd; //파이프 0 1 두개의 2차원 배열
	int		cmd_num; //명령의 총 갯수
	t_node	*node_head;
	t_node	*node_tail;
} t_main_node;

// env $LS 이런 느낌인가?
typedef struct s_symtab_val
{
	int						val_type; //근데 이 타입이 함수타입이라는게 무슨 뜻인지 모르겠다. 함수타입이면 0 변수타입이면 1로 지정해주기
	char					*val; //쉘 변수에만 해당
	struct s_symtab_val		*next;
	t_node					*func_body;//함수인경우만 해당 되는 것 같다.
} t_symtab_val;

typedef struct s_symtab
{
	int				level;//0번째 레벨은 전역변수를 넣어놓을 것이다. 1부터 쉘들의 지역변수
	t_symtab_val	*first;
	t_symtab_val	*last;
} t_symtab;

struct s_symtab_stack
{
	int			symtab_count;//현재 있는 기호 태이블의 수
	t_symtab	*symtab_list[256];//기호테이블을 가리키는 포인터 배열
	t_symtab	*global_symtab;//0번째 심볼태이블
	t_symtab	*local_symtab;//이건 가장 위에 있는 심볼태이블.
} t_symtab_stack;

#endif
