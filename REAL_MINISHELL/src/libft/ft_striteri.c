/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 08:14:03 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 08:14:19 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	unsigned int	slen;

	if (s && f)
	{
		slen = ft_strlen(s);
		i = 0;
		while (i < slen)
		{
			f(i, &s[i]);
			i++;
		}
	}
}
