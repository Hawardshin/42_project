/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:22:28 by joushin           #+#    #+#             */
/*   Updated: 2022/07/08 15:44:49 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (c == s[i])
		return ((char *) &s[i]);
	while (i)
	{
		i--;
		if (c == s[i])
			return ((char *) &s[i]);
	}
	return (0);
}
