/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:14:42 by joushin           #+#    #+#             */
/*   Updated: 2022/11/12 17:33:16 by joushin          ###   ########.fr       */
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

	tok_buff = malloc(sizeof(char) * 1000000000);
	env_buff = malloc(sizeof(char) * 1000000000);
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
	{
		move_char(src);
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
		{
			while ((token_case(see_char(src)) != D_QUOTES) && (see_char(src) != ENDOF))
			{
				tok_buff[i] = move_char(src);
				i++;
			}
		}
		tok_buff[i] = '\0';
		i++;
		if (token_case(see_char(src)) != D_QUOTES)
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
		// if (k != 0)
		// 	move_char(src);
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
	// else if (see_char(src) == EOF)
	// {
	// 	tok->text = "EOF";
	// 	tok->tok_type = EOF_TOK;
	// 	free(env_buff);
	// 	free(tok_buff);
	// 	return (tok);
	// }
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
	back = NULL;
}

void	merge_argv_tok(t_main_token *tok)
{
	t_token	*tmp;

	tmp = tok->start_token;
	while (tmp != NULL)
	{
		if ((tmp->tok_type == ARGV_TOK) && tmp->next && (tmp->next->tok_type == ARGV_TOK))
			merge_two_tok(tmp, tmp->next);
		else
			tmp = tmp->next;
	}
}

void	delete_all_space_tok(t_main_token *tok)
{
	t_token	*tmp;
	t_token	*ntmp;

	tmp = tok->start_token;
	while (tmp)
	{
		if (tmp->tok_type == SPACE_TOK)
		{
			if (!tmp->bef)
			{
				free(tmp);
				tmp =tmp->next;
				tmp->bef = NULL;
				tok->start_token = tmp;
			}
			else
			{
				ntmp = tmp->next;
				tmp->bef->next = tmp->next;
				if (tmp->next != NULL)
					tmp->next->bef = tmp->bef;
				free(tmp);
				tmp = ntmp;
			}
		}
		else
			tmp = tmp->next;
	}
}

t_main_token	*tokenize(t_readline *src)
{
	t_main_token	*main_tok;
	t_token			*tmp;
	t_token			*next;

	main_tok = malloc(sizeof(t_main_node));
	if (!main_tok)
		return (NULL);
	ft_memset(main_tok, 0, sizeof(t_main_node));
	tmp = create_token(src);
	tmp->bef = NULL;
	tmp->next = NULL;
	main_tok->start_token = tmp;
	main_tok->end_token = tmp;
	while (tmp)
	{
		next = create_token(src);
		tmp->next = next;
		if (!next)
		{
			main_tok->end_token = next;
			break;
		}
		// printf("ss: %s\n",tmp->text);
		next->bef = main_tok->end_token;
		next->next = NULL;
		main_tok->token_num++;
		tmp = next;
	}//여기까지가 모든 토큰을 다 만들어 주는것 //space까지
	// Print_all_token(main_tok->start_token);
	merge_argv_tok(main_tok);
	Print_all_token((main_tok->start_token));
	// delete_all_space_tok(main_tok);
	// Print_all_token((main_tok->start_token));
	return (main_tok);
}
