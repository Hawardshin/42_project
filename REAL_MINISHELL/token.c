/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:14:42 by joushin           #+#    #+#             */
/*   Updated: 2022/11/11 22:25:50 by joushin          ###   ########.fr       */
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
			return (tok);
		}
	}
	else if (token_case(see_char(src)) == D_QUOTES)
	{	print_src_char(src);
		move_char(src);
		print_src_char(src);
		while ((token_case(see_char(src)) != D_QUOTES) && (see_char(src) != ENDOF))
		{
			print_src_char(src);
			if (token_case(see_char(src)) == DOLLAR)
			{
				move_char(src);
				while (token_case(see_char(src)) == CHAR)
				{
					env_buff[k] = move_char(src);
					k++;
				}
				env_buff[k] = '\0';
				printf("env_BUFF::%s\n",env_buff);
				env_text = getenv(env_buff);
				printf("envtext:%s\n",env_text);
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
			return (tok);
		}
	}
	return (NULL);

}
//토큰의 구분자에 해당하면 -1


t_token	*tokenize(t_readline *src)
{
	t_token	*main_tok_node = create_token(src);
	printf("%s\n",main_tok_node->text);

	// main_tok_node = malloc (sizeof (t_token));
	// if (!main_tok_node)
	// 	return (NULL);
	// ft_memset(main_tok_node, 0, sizeof (t_token));
	// main_tok_node->next = NULL;
	do
	{
		main_tok_node ->next =  create_token(src);
	}
	while (main_tok_node->next != NULL);
	Print_all_token(main_tok_node);
	return (main_tok_node);
}
