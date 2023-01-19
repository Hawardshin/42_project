/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:19:41 by joushin           #+#    #+#             */
/*   Updated: 2022/09/05 19:58:30 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft__strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft__memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	if (d < s)
	{
		while (len--)
			*d++ = *s++;
	}
	else if (d > s)
	{
		while (len--)
		{
			d[len] = s[len];
		}
	}
	return (dst);
}

size_t	ft__strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft__strlen(src));
	while (i + 1 < dstsize)
	{
		if (src[i])
		{
			dst[i] = src[i];
			i++;
		}
		else
			break ;
	}
	dst[i] = '\0';
	return (ft__strlen(src));
}

char	*ft__strdup(const char *s1)
{
	char	*result;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft__strlen(s1);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		ft_putstr_fd("Memory allocate fail\n", 2);
	ft__strlcpy(result, s1, len + 1);
	return (result);
}

char	*ft__strjoin(char *s1, char *s2)
{
	char	*retstr;
	size_t	i;
	size_t	j;

	i = 0;
	retstr = malloc(sizeof(char) * (ft__strlen(s1) + ft__strlen(s2) + 1));
	if (!retstr)
		ft_putstr_fd("Memory allocate fail\n", 2);
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
	free(s1);
	retstr[i + j] = '\0';
	return (retstr);
}
