/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:24:53 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 16:53:41 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*del_all(int now, t_list *start_lst, void (*del)(void *))
{
	t_list	*tmp;

	while (now)
	{
		tmp = start_lst;
		start_lst = start_lst -> next;
		del(tmp);
		free(tmp);
		now--;
	}
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		l_len;
	int		i;
	t_list	*start_lst;

	start_lst = lst;
	i = 0;
	if (lst && f && del)
	{
		l_len = ft_lstsize(lst);
		while (i < l_len)
		{
			lst = (t_list *)malloc(sizeof(t_list));
			if (!lst)
				return (del_all(l_len, start_lst, del));
			lst = f(lst);
			lst = lst -> next;
			i++;
		}
	}
	return (NULL);
}
