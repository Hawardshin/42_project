/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 08:23:00 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 12:01:03 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*retstr;
	unsigned int	i;

	if (!s || !f)
		return (0);
	i = 0;
	retstr = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!retstr)
		return (0);
	while (s[i])
	{
		retstr[i] = f(i, s[i]);
		i++;
	}
	retstr[i] = '\0';
	return (retstr);
}
