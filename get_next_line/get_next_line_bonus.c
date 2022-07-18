/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:52:14 by joushin           #+#    #+#             */
/*   Updated: 2022/07/18 11:32:13 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	check_new_line(char *buf)
{
	int	idx;

	idx = 0;
	while (buf[idx])
	{
		if (buf[idx] == '\n')
			return (idx + 1);
		idx++;
	}
	return (0);
}

char	*ft_read_line(int fd, char *backup)
{
	char	buff[BUFFER_SIZE + 1];
	ssize_t	read_size;
	char	*to_read;

	to_read = backup;
	while (!check_new_line(buff))
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size == 0)
			return (to_read);
		if (read_size < 0 || !buff[0])
		{
			if (backup)
				free(backup);
			return (NULL);
		}
		buff[read_size] = '\0';
		if (!to_read)
			to_read = ft_strdup(buff);
		else
			to_read = ft_strjoin(to_read, buff);
	}
	return (to_read);
}

char	*ft_get_line(char **str)
{
	char	*ret_line;
	int		l;
	int		i;
	int		slen;

	slen = ft_strlen(*str);
	i = 0;
	l = check_new_line(*str);
	ret_line = (char *)malloc(sizeof(char) * (l +1));
	if (!ret_line)
		return (NULL);
	while (i < l)
	{
		ret_line[i] = *(*str + i);
		i++;
	}
	ret_line[i] = '\0';
	ft_memmove(*str, *str + l, slen - l);
	(*str)[slen - l] = '\0';
	return (ret_line);
}

char	*get_next_line(int fd)
{
	static char	*backup[OPEN_FD_MAX];
	char		*ret_line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_FD_MAX)
		return (NULL);
	backup[fd] = ft_read_line(fd, backup[fd]);
	if (!backup[fd])
		return (NULL);
	if (!check_new_line(backup[fd]))
	{
		if ((backup[fd][0]))
			ret_line = ft_strdup(backup[fd]);
		else
			ret_line = NULL;
		free(backup[fd]);
		backup[fd] = NULL;
		return (ret_line);
	}
	ret_line = ft_get_line(&backup[fd]);
	if (ret_line == NULL)
		return (NULL);
	return (ret_line);
}
