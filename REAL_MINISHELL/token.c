/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:14:42 by joushin           #+#    #+#             */
/*   Updated: 2022/11/16 19:16:59 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/node.h"
#include "./libft/libft.h"
#include "./include/just_for_test.h"
#include "./include/utils.h"
#include <errno.h>

char	move_char(t_readline *src) //움직이기까지 함.
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

int	ft_token_len(t_readline *src)
{
	int		len;
	int		i;
	char	*tmp;

	tmp = src->buffer;
	len = 0;
	i = src->now_pos;
	if (i == -2)
		i = 0;
	while (token_case(see_char(src)) != QUOTES && see_char(src) != ENDOF)
	{
		move_char(src);
		len++;
	}
	src->now_pos = i;
	return (len);
}

t_token	*create_quotes(t_readline *src)
{
	t_token	*tok;
	int		len;
	int		i;

	i = 0;
	move_char(src);
	tok = malloc(sizeof(t_token));
	len = ft_token_len(src);
	tok->text = malloc(sizeof(char) * (len + 1));
	tok->text_len = len;
	while (token_case(see_char(src)) != QUOTES && see_char(src) != ENDOF)
	{
		tok->text[i] = move_char(src);
		i++;
	}
	tok->text[i] = '\0';
	if (see_char(src) == ENDOF)
		g_state.exit_code = 258;
	else
		move_char(src);
	tok->tok_type = ARGV_TOK;
	return (tok);
}

int	ft_env_len(t_readline *src)
{
	int	len = 0;
	int	tmp = src->now_pos;
	while (token_case(see_char(src)) == DOLLAR)//달러뒤에 달러인 경우는 무시
	{
		move_char(src);
		len++;
	}
	while (token_case(see_char(src)) == CHAR)
	{
		move_char(src);
		len++;
	}
	src->now_pos = tmp;
	return (len);
}

int	ft_all_len(t_readline *src)
{
	char	*env_buff;
	int		len;
	int		i;
	int		tmp;

	len = 0;
	tmp = src->now_pos;
	while ((token_case(see_char(src)) != D_QUOTES) && (see_char(src) != ENDOF))
	{
		if (token_case(move_char(src)) == DOLLAR)
		{
			i = 0;
			env_buff = malloc (ft_env_len(src) + 1);
			while (token_case(see_char(src)) == DOLLAR)//달러뒤에 달러인 경우는 무시
				env_buff[i++] = move_char(src);
			while (token_case(see_char(src)) == CHAR)
				env_buff[i++] = move_char(src);
			env_buff[i] = '\0';
			len += ft_strlen(get_env(env_buff));
			my_free((void **) &env_buff);
		}
		len++;
	}
	src->now_pos = tmp;
	return (len);
}

char	*make_env_text(t_readline *src)
{
	char	*env_buff;
	int		k;
	char	*env_text;

	k = 0;
	env_buff = malloc (ft_env_len(src) + 1);
	move_char(src);
	k = 0;
	env_buff = malloc (ft_env_len(src) + 1);
	k = 0;
	while (token_case(see_char(src)) == DOLLAR)//달러뒤에 달러인 경우는 무시
		env_buff[k++] = move_char(src);
	while (token_case(see_char(src)) == CHAR)
		env_buff[k++] = move_char(src);
	env_buff[k] = '\0';
	env_text = get_env(env_buff);
	my_free((void **) &env_buff);
	if (k == 0)
		env_text = "$";
	return (env_text);
}

char	*make_double_tok(t_readline *src)
{
	char	*tok_buff;
	int		i;
	int		k;
	char	*env_text;

	i = 0;
	k = 0;
	tok_buff  = malloc(ft_all_len(src) + 1);
	while ((token_case(see_char(src)) != D_QUOTES) && (see_char(src) != ENDOF))
	{
		if (token_case(see_char(src)) == DOLLAR)
		{
			env_text = make_env_text(src);
			while (env_text && *env_text)
				tok_buff[i++] = *env_text++;
			tok_buff[i] = '\0';
		}
		else
			tok_buff[i++] = move_char(src);
	}
	tok_buff[i] = '\0';
	return (tok_buff);
}

t_token	*create_d_quotes(t_readline *src)
{
	t_token	*tok;

	move_char(src);
	tok = malloc(sizeof(t_token));
	ft_memset(tok, 0, sizeof(t_token));
	tok->text = make_double_tok(src);
	if (token_case(see_char(src)) != D_QUOTES)
		g_state.exit_code = 258;
	else
		move_char(src);
	tok->text_len = ft_strlen(tok->text);
	tok->tok_type = ARGV_TOK;
	return (tok);
}

t_token	*create_space_tok(t_readline *src)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	ft_memset(tok, 0, sizeof(t_token));
	while (token_case(see_char(src)) == SPACE_B && see_char(src) != ENDOF)
		move_char(src);
	tok->text = "SPACE";
	tok->tok_type = SPACE_TOK;
	return (tok);
}

t_token	*create_pipe_tok(t_readline *src)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	ft_memset(tok, 0, sizeof(t_token));
	move_char(src);
	tok->text = "PIPE'|'";
	tok->tok_type = PIPE_TOK;
	return (tok);
}

t_token	*create_direct_tok(t_readline *src)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	ft_memset(tok, 0, sizeof(t_token));
	move_char(src);
	if (token_case(see_char(src)) == DIRECT)
	{
		move_char(src);
		tok->text = "<<";
	}
	else
		tok->text = "<";
	tok->tok_type = IO_TOK;
	return (tok);
}

t_token	*create_redirect_tok(t_readline *src)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	ft_memset(tok, 0, sizeof(t_token));
	move_char(src);
	if (token_case(see_char(src)) == RE_DIRECT)
	{
		move_char(src);
		tok->text = ">>";
	}
	else
		tok->text = ">";
	tok->tok_type = IO_TOK;
	return (tok);
}

// t_token	*create_dollar_tok(t_readline *src)
// {
// 	t_token	*tok;

// 	tok = malloc(sizeof(t_token));
// 	ft_memset(tok, 0, sizeof(t_token));

// 	move_char(src);
// 	while (token_case(see_char(src)) == DOLLAR)
// 	{
// 		env_buff[k] = move_char(src);
// 		k++;
// 	}
// 	while (token_case(see_char(src)) == CHAR)
// 	{
// 		env_buff[k] = move_char(src);
// 		k++;
// 	}
// 	env_buff[k] = '\0';
// 	env_text = get_env(env_buff);//이거 환경변수 세팅해서 바꿔야되는데 일단 토큰부터 다 만들고 진행할 예정
// 	my_free((void**)&env_buff);
// 	if (k == 0) //달러 하나인 경우에는 $로 봐야해요
// 		env_text = "$";
// 	while (env_text && *env_text)
// 		tok_buff[i++] = *env_text++;
// 	tok_buff[i] = '\0';
// 	i++;
// 	tok->text = malloc(sizeof(char) * (i));
// 	tok->text_len = i;
// 	while (j < i)
// 	{
// 		tok->text[j] = tok_buff[j];
// 		j++;
// 	}
// 	my_free((void**)&tok_buff);
// 	tok->text_len = j;
// 	tok->tok_type = ARGV_TOK;
// 	return (tok);
// }

t_token	*create_token(t_readline *src)
{
	t_token	*tok;
	char	*tok_buff;
	char	*env_buff;
	char	*env_text;
	int		i;
	int		j;
	int		k;

	tok_buff = malloc(sizeof(char) * 1000);
	env_buff = malloc(sizeof(char) * 1000);
	tok = malloc(sizeof(t_token));
	i = 0;
	j = 0;
	k = 0;
	if (!tok || !tok_buff)
		return (NULL);
	ft_memset(tok, 0, sizeof(t_token));
	if (token_case(see_char(src)) == QUOTES)//작은 따옴표인 경우 쭉 토큰화를 하고
		return (create_quotes(src));
	else if (token_case(see_char(src)) == D_QUOTES)
		return (create_d_quotes(src));
	else if (token_case(see_char(src)) == SPACE_B)
		return (create_space_tok(src));
	else if (token_case(see_char(src)) == PIPE)
		return (create_pipe_tok(src));
	else if (token_case(see_char(src)) == DOLLAR)
	{
		move_char(src);
		while (token_case(see_char(src)) == DOLLAR)
		{
			env_buff[k] = move_char(src);
			k++;
		}
		while (token_case(see_char(src)) == CHAR)
		{
			env_buff[k] = move_char(src);
			k++;
		}
		env_buff[k] = '\0';
		env_text = get_env(env_buff);//이거 환경변수 세팅해서 바꿔야되는데 일단 토큰부터 다 만들고 진행할 예정
		my_free((void**)&env_buff);
		if (k == 0) //달러 하나인 경우에는 $로 봐야해요
			env_text = "$";
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
		my_free((void**)&tok_buff);
		tok->text_len = j;
		tok->tok_type = ARGV_TOK;
		return (tok);
	}
	else if (token_case(see_char(src)) == DIRECT)
		return (create_direct_tok(src));
	else if (token_case(see_char(src)) == RE_DIRECT)
		return (create_redirect_tok(src));
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
		my_free((void**)&tok_buff);
		my_free((void**)&env_buff);
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
	while (back && back->text[j])
	{
		buff[i++] = back->text[j++];
	}
	buff[i] = '\0';
	my_free((void**)&front->text);
	front->text = buff;
	if (i == 0)
		i++;
	front->text_len = i;
	front->next = back->next;
	my_free((void**)&back->text);
	my_free((void**)&back);
	back = NULL;
}

void	merge_argv_tok(t_main_token *tok)
{
	t_token	*tmp;

	tmp = tok->start_token;
	while (tmp->next != NULL)
	{
		if ((tmp->tok_type == ARGV_TOK) && ((tmp->next->tok_type) == ARGV_TOK))
			merge_two_tok(tmp, tmp->next);
		else
			tmp = tmp->next;
	}
	// delete_all_null_tok(tok);
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
			if (tmp->bef==NULL)//시작 토큰이라면
			{
				ntmp = tmp->next;
				my_free((void**)&tmp);
				tmp = ntmp;
				if (tmp)
					tmp->bef = NULL;
				tok->start_token = tmp;
			}
			else
			{
				ntmp = tmp->next;
				tmp->bef->next = ntmp;
				if (ntmp)
					ntmp->bef = tmp->bef;
				my_free((void**)&tmp);
				tmp = ntmp;
			}
		}
		else
		{
			if (tmp->next)
				tmp->next->bef = tmp;
			tmp = tmp->next;
		}
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
		next->bef = main_tok->end_token;
		next->next = NULL;
		main_tok->token_num++;
		tmp = next;
	}//여기까지가 모든 토큰을 다 만들어 주는것 //space까지
	merge_argv_tok(main_tok);
	// Print_all_token((main_tok->start_token));
	delete_all_space_tok(main_tok);
	// Print_all_token((main_tok->start_token));
	return (main_tok);
}
