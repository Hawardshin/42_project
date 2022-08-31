/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:42:40 by joushin           #+#    #+#             */
/*   Updated: 2022/08/31 18:36:03 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

void	my_free(char **to_free)
{
	free(*to_free);
	*to_free = NULL;
}

char	*ft_mstrdup(const char *s1)
{
	char	*result;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		print_error(0, NULL);
	ft_strlcpy(result, s1, len + 1);
	return (result);
}

char	*ft_mstrjoin(char const *s1, char const *s2)
{
	char	*retstr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	retstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!retstr)
		print_error(0, NULL);
	while (s1[i])
	{
		retstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		retstr[i + j] = s2[j];
		j++;
	}
	retstr[i + j] = '\0';
	return (retstr);
}

t_px	*mlst_find(int idx, t_data *data)
{
	t_px	*node;

	node = data->cmd_node_head;
	while (node)
	{
		if (node->idx == idx)
			return (node);
		node = node ->next;
	}
	return (NULL);
}

pid_t	mfork(void)
{
	pid_t	rpid;

	rpid = fork();
	if (rpid == -1)
	{
		perror("fork error ");
		exit(1);
	}
	return (rpid);
}
