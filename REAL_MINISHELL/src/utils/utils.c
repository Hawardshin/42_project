/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:19:34 by joushin           #+#    #+#             */
/*   Updated: 2022/11/24 17:21:06 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/just_for_test.h"
#include "../../include/utils.h"
#include "../libft/libft.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (!(str1[i] == '\0' || str2[i] == '\0'))
	{
		if (str1[i] != str2[i])
			break ;
		i++;
	}
	return (str1[i] - str2[i]);
}

void	my_free(void **to_free)
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

pid_t	mfork(void)
{
	pid_t	rpid;

	rpid = fork();
	if (rpid == -1)
	{
		g_state.exit_code = 1;
		perror("fork error ");
		exit(1);
	}
	return (rpid);
}
