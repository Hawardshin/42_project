/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:34:09 by joushin           #+#    #+#             */
/*   Updated: 2022/11/15 10:28:51 by joushin          ###   ########.fr       */
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

// #define HERE_DOC_NODE 1000 // <<
// #define APPEND_NODE 2000 //?
// #define OPEN_NODE 3000
// #define WRITE_NODE 4000

typedef enum e_io_type
{
	HERE_DOC_NODE = 10, // <<
	APPEND_NODE, //>>
	OPEN_NODE, //<
	WRITE_NODE // >
}	t_io_type;


void	print_error(int Flag, char *s);

typedef struct	s_node
{
	int				idx;	//몇번 째 노드인지
						//2개는 명령인 경우만 채워지고 아닌경우 NULL로 채워짐
	char			**cmd;	// 명령어 이차원 배열인 이유는 execve를 하기 위해 1번에 명령어와 그 뒤에 인자들.
	char			*cmd_path[2];	//명령어 경로
	char			*file;  //이건 IO_TOKEN일떄만 들어간다.
	t_io_type		node_type; //IO_TOKEN일 때 어떤 IO_NODE 인지
	struct s_node	*next;
	struct s_node	*prev;
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
