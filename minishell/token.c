/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:14:42 by joushin           #+#    #+#             */
/*   Updated: 2022/11/10 17:50:52 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/node.h"
#include "./libft/libft.h"
#include "./include/parse_utils.h"
#include <errno.h>

t_token	*create_token(char *str)
{
	t_token	*tok;
	char	*nstr;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	ft_memset(tok, 0, sizeof(t_token));
	if (str == NULL) //eof 토큰 만들기
	{
		// printf("this is eof\n");
		tok->eof = 1;
		return (tok);
	}
	tok->text_len = ft_strlen(str);
	nstr = malloc(tok->text_len + 1);
	if(!nstr)
	{
		free(tok);
		return NULL;
	}
	ft_strlcpy(nstr, str, tok->text_len + 1);
	free(str);
	tok->text = nstr;
	return (tok);
}

int	check_sep(char a)
{
	if (a == -1)
		return (-1);
	if (a == ' ' || a == '\t' || a == '\n' || a == '<' || a == '>' || a == '$')
		return (0);
	return (1);
}
//토큰의 구분자에 해당하면 -1
int	token_case(t_readline *src)
{
	if (see_char(src) == -1 && src->done_pos == src->bufsize)
		return (1);
	while (check_sep(see_char(src))) //구분자가 있는지 확인하면서 계속 뒤로 늘린다.
	{
		if (see_char(src) == -1)
			return (0);
		move_char(src);
		// printf("move :: %c \n",move_char(src));
	}
	// if (check_sep(see_char(src) == 0))
	// 	move_char(src);
	return (0);
}

t_token	*tokenize(t_readline *src)
{
	char	*token_buff;
	int		i;

	i = 0;
	skip_white_spaces(src);

	if (token_case(src) == 1)
		return(create_token(NULL));
	token_buff = malloc(src->now_pos - src->done_pos + 2);
	if (!token_buff)
		return (NULL);
	// printf("now :%d done:%d buff_size %d\n",src->now_pos, src->done_pos,src->bufsize);
	while (src->done_pos <= src->now_pos)
	{
		// printf("%c\n",src->buffer[src->done_pos]);
		token_buff[i++] = src->buffer[src->done_pos++];
	}
	// if (src->bufsize == src->done_pos)
	// 	src->done_pos--;
	token_buff[i] = 0;
	// printf("ss%s0\n",token_buff);
	return (create_token(token_buff));
}
