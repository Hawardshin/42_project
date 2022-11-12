/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:14:42 by joushin           #+#    #+#             */
/*   Updated: 2022/11/12 14:38:49 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/node.h"
#include "./libft/libft.h"
#include "./include/token.h"
#include "./include/error.h"
#include "./include/just_for_test.h"
#include <errno.h>

char	move_char(t_readline *src)//움직이기까지 함.
{
	char	c1;

	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (0);
	}
	c1 = 0;
	if (src->now_pos == -2)
		src->now_pos = -1;
	else
		c1 = src->buffer[src->now_pos];
	if (++src->now_pos >= src->bufsize)
	{
		src->now_pos = src->bufsize;
		return (ENDOF);
	}
	return (src->buffer[src->now_pos]);
}

char	see_char(t_readline *src)//보기만 함.
{
	int	pos;

	if (!src || !(src->buffer))
	{
		errno = ENODATA;
		return (0);
	}
	pos = src->now_pos;
	if (pos == -2)
		pos++;
	pos++;
	if (pos >= src->bufsize)
		return (ENDOF);
	return (src->buffer[pos]);
}

int	token_case(char a)
{
	if (a == '|')
		return (PIPE);
	if (a == '\'')
		return (QUOTES);
	if (a == '\"')
		return (D_QUOTES);
	if (a == ' ')
		return (SPACE_B);
	if (a == '$')
		return (DOLLAR);
	if (a == '<')
		return (DIRECT);
	if (a == '>')
		return (RE_DIRECT);
	if (a == ENDOF)
		return (ENDOF);
	return (CHAR);
}

t_token	*create_token(t_readline *src)
{
	t_token	*tok;
	char	*tok_buff;
	char	*env_buff;
	char	*env_text;
	int		i;
	int		j;
	int		k;

	tok_buff = malloc (sizeof(char) * 1000000000);
	env_buff = malloc (sizeof(char) * 1000000000);
	tok = malloc(sizeof(t_token));
	i = 0;
	j = 0;
	k = 0;
	if (!tok || !tok_buff)
		return (NULL);
	ft_memset(tok, 0, sizeof(t_token));
	if (token_case(see_char(src)) == QUOTES)//작은 따옴표인 경우 쭉 토큰화를 하고
	{
		move_char(src);
		while (token_case(see_char(src)) != QUOTES && see_char(src) != ENDOF)
		{
			tok_buff[i] = move_char(src);
			i++;
		}
		tok_buff[i] = '\0';
		i++;
		if (see_char(src) == ENDOF)
			syntax_error();
		else
		{
			move_char(src);
			tok->text = malloc(sizeof(char) * (i));
			tok->text_len = i;
			while (j < i)
			{
				tok->text[j] = tok_buff[j];
				j++;
			}
			free(tok_buff);
			tok->text_len = j;
			tok->tok_type = ARGV_TOK;
			return (tok);
		}
	}
	else if (token_case(see_char(src)) == D_QUOTES)
	{	print_src_char(src);
		move_char(src);
		print_src_char(src);
		while ((token_case(see_char(src)) != D_QUOTES) && (see_char(src) != ENDOF))
		{
			// print_src_char(src);
			if (token_case(see_char(src)) == DOLLAR)
			{
				move_char(src);
				while (token_case(see_char(src)) == CHAR)
				{
					env_buff[k] = move_char(src);
					k++;
				}
				env_buff[k] = '\0';
				// printf("env_BUFF::%s\n",env_buff);
				env_text = getenv(env_buff);//이거 환경변수 세팅해서 바꿔야되는데 일단 토큰부터 다 만들고 진행할 예정
				// printf("envtext:%s\n",env_text);
				free(env_buff);
				while (env_text && *env_text)
					tok_buff[i++] = *env_text++;
			}
			else
				tok_buff[i++] = move_char(src);
		}
		tok_buff[i] = '\0';
		i++;
		if (see_char(src) == ENDOF)
			syntax_error();
		else
		{
			move_char(src);
			tok->text = malloc(sizeof(char) * (i));
			tok->text_len = i;
			while (j < i)
			{
				tok->text[j] = tok_buff[j];
				j++;
			}
			free(tok_buff);
			tok->text_len = j;
			tok->tok_type = ARGV_TOK;
			return (tok);
		}
	}
	else if (token_case(see_char(src)) == SPACE_B)
	{
		while (token_case(see_char(src)) == SPACE_B && see_char(src) != ENDOF)
		{
			move_char(src);
		}
		tok->text = "SPACE";
		tok->tok_type =SPACE_TOK;
		free(env_buff);
		free(tok_buff);
		return (tok);
	}
	else if (token_case(see_char(src)) == PIPE)
	{
		move_char(src);
		tok->text = "PIPE'|'";
		tok->tok_type = PIPE_TOK;
		free(env_buff);
		free(tok_buff);
		return (tok);
	}
	else if (token_case(see_char(src)) == DOLLAR)
	{
		move_char(src);
		while (token_case(see_char(src)) == CHAR)
		{
			env_buff[k] = move_char(src);
			k++;
		}
		env_buff[k] = '\0';
		env_text = getenv(env_buff);//이거 환경변수 세팅해서 바꿔야되는데 일단 토큰부터 다 만들고 진행할 예정
		// printf("envtext:%s\n",env_text);
		free(env_buff);
		while (env_text && *env_text)
			tok_buff[i++] = *env_text++;
		tok_buff[i] = '\0';
		i++;
		move_char(src);
		tok->text = malloc(sizeof(char) * (i));
		tok->text_len = i;
		while (j < i)
		{
			tok->text[j] = tok_buff[j];
			j++;
		}
		free(tok_buff);
		tok->text_len = j;
		tok->tok_type = ARGV_TOK;
		return (tok);
	}
	else if (token_case(see_char(src)) == DIRECT)
	{
		move_char(src);
		if (token_case(see_char(src)) == DIRECT)
		{
			move_char(src);
			tok->text = "<<";
		}
		else
			tok->text = "<";
		tok->tok_type = IO_TOK;
		free(env_buff);
		free(tok_buff);
		return (tok);
	}
	else if (token_case(see_char(src)) == RE_DIRECT)
	{
		move_char(src);
		if (token_case(see_char(src)) == RE_DIRECT)
		{
			move_char(src);
			tok->text = ">>";
		}
		else
			tok->text = ">";
		tok->tok_type = IO_TOK;
		free(env_buff);
		free(tok_buff);
		return (tok);
	}
	else if (see_char(src) == EOF)
	{
		tok->text = "EOF";
		tok->tok_type = EOF_TOK;
		free(env_buff);
		free(tok_buff);
		return (tok);
	}
	else if (token_case(see_char(src)) == CHAR)
	{
		while (token_case(see_char(src)) == CHAR && see_char(src) != ENDOF)
		{
			tok_buff[i] = move_char(src);
			i++;
		}
		tok_buff[i] = '\0';
		i++;
		tok->text = malloc(sizeof(char) * (i));
		tok->text_len = i;
		while (j < i)
		{
			tok->text[j] = tok_buff[j];
			j++;
		}
		free(tok_buff);
		free(env_buff);
		tok->text_len = j;
		tok->tok_type = ARGV_TOK;
		return (tok);
	}
	return (NULL);

}

// 1. argv끼리 space없이 뭉쳐있는경우 하나의 argv_tok로 합쳐주기.
// 2. space token은 다 삭제

void	merge_two_tok(t_token *front, t_token *back)
{
	char	*buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buff = malloc (front->text_len + back->text_len + 1);
	while (front -> text[i])
	{
		buff[i] = front -> text[i];
		i++;
	}
	while (back->text[j])
	{
		buff[i++] = back->text[j++];
	}
	buff[i] = '\0';
	free(front->text);
	front->text = buff;
	front->next = back->next;
	free(back->text);
	free(back);
}

void	merge_argv_tok(t_token *tok)
{
	t_token	*end;

	end = tok;
	while ((end->tok_type != EOF_TOK) && (end!= NULL))
	{
		if ((end->tok_type == ARGV_TOK) && (end->next->tok_type == ARGV_TOK))
		{
			// merge_two_tok(&end, &(end->next));
			merge_two_tok(end,end->next);
		}
		else
			end = end->next;
	}
}

t_token	*tokenize(t_readline *src)
{
	t_token	*end;
	t_token	*tmp;
	t_token	*main_tok_node;

	main_tok_node = create_token(src);
	main_tok_node ->bef = NULL;
	end = main_tok_node;
	while (end->tok_type != EOF_TOK && end)
	{
		tmp = create_token(src);
		// printf("ss: %s\n",tmp->text);
		tmp->bef = end;
		end->next = tmp;
		end = tmp;
	}//여기까지가 모든 토큰을 다 만들어 주는것 //space까지
	Print_all_token(main_tok_node);
	merge_argv_tok(main_tok_node);
	Print_all_token(main_tok_node);
	return (main_tok_node);
}
