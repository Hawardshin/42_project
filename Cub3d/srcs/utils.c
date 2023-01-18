/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:16:51 by joushin           #+#    #+#             */
/*   Updated: 2023/01/16 15:24:38 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	error_handle(char *s)
{
	ft_eprintf("error\n");
	ft_eprintf("%s", s);
	exit(1);
}

char	*ft_strjoin_no_nl(char *dest, char *src)
{
	int		d_len;
	int		s_len;
	char	*ret;
	int		i;
	int		j;

	d_len = ft_strlen(dest);
	s_len = ft_strlen(src);
	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * (d_len + s_len));
	if (!ret)
		error_handle("Memory allocate fail\n");
	while (dest[i])
	{
		ret[i] = dest[i];
		i++;
	}
	free(dest);
	while (src[j] && src[j] != '\n')
		ret[i++] = src[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_strdup_no_nl(char *str)
{
	int		len;
	char	*ret;
	int		i;

	i = 0;
	len = ft_strlen(str);
	ret = (char *)malloc(sizeof(char) * len);
	if (!ret)
		error_handle("Memory allocate fail\n");
	while (str[i] && str[i] != '\n')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
