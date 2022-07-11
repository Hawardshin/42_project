/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:10:56 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 17:27:53 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	while ((*lst)-> next != NULL)
	{
		tmp = *lst;
		*lst = (*lst)-> next;
		ft_lstdelone(tmp, del);
	}
	ft_lstdelone(*lst, del);
	*lst = NULL;
}
