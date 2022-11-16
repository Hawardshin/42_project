/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:47:50 by joushin           #+#    #+#             */
/*   Updated: 2022/11/16 22:48:01 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

static char	*ft_make_cmd_path(t_main_node *px, char *text, int i)
{
	char	*tmp;
	char	*ptmp;

	tmp = ft_mstrjoin("/", text);
	ptmp = ft_mstrjoin(px->path[i], tmp);
	my_free((void **) &tmp);
	return (ptmp);
}

char	*find_path(char *text, t_main_node *main_node)
{
	int			i;
	char		*ptmp;
	struct stat	st;

	i = -1;
	while (main_node -> path[++i])
	{
		if (ft_strncmp(text, "/", 1) != 0)
			ptmp = ft_make_cmd_path(main_node, text, i);
		else
			ptmp = ft_mstrdup(text);
		if (stat(ptmp, &st) == 0)
			return (ptmp);
		my_free((void **)&ptmp);
	}
	return (NULL);
}
