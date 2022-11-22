/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:14:42 by joushin           #+#    #+#             */
/*   Updated: 2022/11/22 22:03:36 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

t_token	*create_token(t_readline *src)
{
	if (token_case(see_char(src)) == QUOTES)
		return (create_quotes(src));
	else if (token_case(see_char(src)) == D_QUOTES)
		return (create_d_quotes(src));
	else if (token_case(see_char(src)) == SPACE_B)
		return (create_space_tok(src));
	else if (token_case(see_char(src)) == PIPE)
		return (create_pipe_tok(src));
	else if (token_case(see_char(src)) == DOLLAR)
		return (create_dollar_tok(src));
	else if (token_case(see_char(src)) == DIRECT)
		return (create_direct_tok(src));
	else if (token_case(see_char(src)) == RE_DIRECT)
		return (create_redirect_tok(src));
	else if (token_case(see_char(src)) == CHAR)
		return (create_char_tok(src));
	return (NULL);
}

t_main_token	*main_tok_init(t_token *tmp)
{
	t_main_token	*main_tok;

	main_tok = malloc(sizeof(t_main_node));
	if (!main_tok)
		return (NULL);
	ft_memset(main_tok, 0, sizeof(t_main_node));
	main_tok->start_token = tmp;
	main_tok->end_token = tmp;
	return (main_tok);
}

t_main_token	*tokenize(t_readline *src)
{
	t_main_token	*main_tok;
	t_token			*tmp;
	t_token			*next;

	tmp = create_token(src);
	main_tok = main_tok_init(tmp);
	while (tmp)
	{
		next = create_token(src);
		tmp->next = next;
		if (!next)
		{
			main_tok->end_token = tmp;
			break ;
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
