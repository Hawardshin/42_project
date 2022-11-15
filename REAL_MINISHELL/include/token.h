/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:07:06 by joushin           #+#    #+#             */
/*   Updated: 2022/11/15 09:36:56 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "node.h"


enum e_char_case
{
	ENDOF = -1,
	CHAR = 10,
	PIPE , //'|'
	QUOTES , // ''
 	D_QUOTES , // ""
 	SPACE_B , // ' '
 	DOLLAR ,// $
 	DIRECT ,// <
 	RE_DIRECT, // >
} ;
// #define ENDOF -1 //널
// #define CHAR 100
// #define PIPE 101 // |
// #define QUOTES 102 // ''
// #define D_QUOTES 103 // ""
// #define SPACE_B 104 // ' '
// #define DOLLAR 105 // $
// #define DIRECT 106 // <
// #define RE_DIRECT 107 // >

typedef enum e_tok_type
{
	IO_TOK,
 	ARGV_TOK,
	PIPE_TOK,
	SPACE_TOK,
} t_toke_type;


typedef struct	s_readline
{
	char	*buffer;/* 입력 텍스트 */
	int		bufsize;/* 입력 텍스트 크기*/
	int		now_pos;/* 소스 안에서 문자위치*/
} t_readline;

typedef struct	s_token
{
	t_toke_type		tok_type;// I/O_red_token ,argv_token, pipeline_token , space_token
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
