/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:34:09 by joushin           #+#    #+#             */
/*   Updated: 2022/11/16 23:07:16 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include<signal.h>
# include<stdio.h>
# include <sys/wait.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<sys/stat.h>
# include<sys/wait.h>
# include<unistd.h>
# include<stdlib.h>
# include<errno.h>

enum e_char_case
{
	ENDOF = -1,
	CHAR = 10,
	PIPE ,
	QUOTES ,
	D_QUOTES,
	SPACE_B,
	DOLLAR,
	DIRECT,
	RE_DIRECT,
} ;

/*node*/
// >> , >

typedef enum e_outfile_type
{
	APPEND_TYPE=10,
	WRITE_TYPE
}	t_outfile_type;

typedef enum e_tok_type
{
	IO_TOK,
	ARGV_TOK,
	PIPE_TOK,
	SPACE_TOK,
}	t_toke_type;

//<< 의 경우 전부다 이렇게 들어온다.
typedef struct s_heredoc
{
	char				*sep;
	struct s_heredoc	*prev;
	struct s_heredoc	*next;
}	t_heredoc;

//<
typedef struct s_infile_node
{
	char					*file;
	struct s_infile_node	*prev;
	struct s_infile_node	*next;
}	t_infile_node;

// >,>>
typedef struct s_outfile_node
{
	char					*file;
	t_outfile_type			type;
	struct s_outfile_node	*prev;
	struct s_outfile_node	*next;
}	t_outfile_node;

typedef struct s_node
{
	int				idx;
	char			**cmd;
	char			*cmd_path[2];
	t_heredoc		*heardoc_node;
	t_infile_node	*infile_node;
	t_outfile_node	*outfile_node;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_main_node
{
	char	**ev;
	char	**path;
	int		**pipefd;//파이프 0 1 두개의 2차원 배열
	int		cmd_num;//명령의 노드의 총 갯수 - 파이프의 갯수로 생각
	t_node	*node_head;
	t_node	*node_tail;
}	t_main_node;

/*token*/
// I/O_red_token ,argv_token, pipeline_token , space_token
typedef struct s_token
{
	t_toke_type		tok_type;
	int				text_len;
	char			*text;
	struct s_token	*bef;
	struct s_token	*next;
}	t_token;

typedef struct s_main_token
{
	t_token	*start_token;
	t_token	*end_token;
	int		token_num;
}	t_main_token ;

/*env*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_env_main_node
{
	t_env	*head;
	t_env	*tail;
}	t_env_main_node;

typedef struct s_state
{
	t_env_main_node	env_main_node;
	pid_t			pid;
	int				exit_code;
	// int				is_fork;
}	t_state;

/* readline*/
typedef struct	s_readline
{
	char	*buffer;/* 입력 텍스트 */
	int		bufsize;/* 입력 텍스트 크기*/
	int		now_pos;/* 소스 안에서 문자위치*/
} t_readline;
t_state	g_state;

/*token_fuction*/
t_main_token	*tokenize(t_readline *src);
char			see_char(t_readline *src);//보기만 함.
char			move_char(t_readline *src); //움직이기까지 함.
int				token_case(char a);
int				ft_env_len(t_readline *src);
t_token			*create_quotes(t_readline *src);
t_token			*create_d_quotes(t_readline *src);
t_token			*create_space_tok(t_readline *src);
t_token			*create_pipe_tok(t_readline *src);
t_token			*create_dollar_tok(t_readline *src);
t_token			*create_direct_tok(t_readline *src);
t_token			*create_redirect_tok(t_readline *src);
t_token			*create_char_tok(t_readline *src);
void			merge_argv_tok(t_main_token *tok);
void			delete_all_space_tok(t_main_token *tok);
/*env */
void			init_g_state(char **envp);
char			*get_env(char *key);
int				check_syntax(t_token *start_tok);
char			*make_env_text(t_readline *src);
/*node_fuction*/

t_main_node		*make_tok_to_node(t_main_token *tok);
char			*find_path(char *text, t_main_node *main_node);
void			make_hdoc_node(t_node *node, t_token **tmp_tok);
void			make_ifile_node(t_node *node, t_token **tmp_tok);
void			make_ofile_node(t_node *node, t_token **tmp_tok);
void			make_rfile_node(t_node *node, t_token **tmp_tok);
t_node			*make_pipe_node(t_token **tmp_tok, t_main_node *main_node);
t_main_node		*main_init(t_main_token **tok, t_token **tmp_tok, t_node **node);
void			pipe_init(t_main_node *main_node);
#endif
