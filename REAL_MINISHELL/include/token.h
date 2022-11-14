/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:07:06 by joushin           #+#    #+#             */
/*   Updated: 2022/11/14 20:42:16 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "node.h"

#define ENDOF -1 //널
#define CHAR 100
#define PIPE 101 // |
#define QUOTES 102 // ''
#define D_QUOTES 103 // ""
#define SPACE_B 104 // ' '
#define DOLLAR 105 // $
#define DIRECT 106 // <
#define RE_DIRECT 107 // >

#define IO_TOK 10
#define ARGV_TOK 20
#define PIPE_TOK 30
#define SPACE_TOK 40
#define EOF_TOK 50
#define MAIN_TOK 60

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

t_main_token	*tokenize(t_readline *src);
char			see_char(t_readline *src);//보기만 함.
char			move_char(t_readline *src); //움직이기까지 함.

#endif
