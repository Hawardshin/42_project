/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:51:54 by joushin           #+#    #+#             */
/*   Updated: 2023/01/22 16:13:06 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

t_map_type	check_type(char a)
{
	if (a == 'N' || a == 'S' || a == 'E' || a == 'W')
		return (PLAYER);
	else if (a == '1')
		return (WALL);
	else if (a == '0')
		return (EMPTY);
	else if (a == ' ')
		return (SPACE);
	else
		return (ERROR);
}

char	*get_next_line_no_nl(int fd)
{
	char	*ret;
	char	*tmp;

	ret = get_next_line(fd);
	if (ret == NULL)
		return (NULL);
	tmp = ft_strdup_no_nl(ret);
	if (tmp == NULL)
		return (NULL);
	free(ret);
	ret = tmp;
	return (ret);
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

void	free_strs(char *str, char **splits)
{
	int	i;

	free(str);
	i = 0;
	if (splits == NULL)
		return ;
	while (splits[i] != NULL)
	{
		free(splits[i]);
		i++;
	}
	free(splits);
}
