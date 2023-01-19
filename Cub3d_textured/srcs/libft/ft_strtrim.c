/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 10:40:54 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 13:17:37 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	check_in(char a, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == a)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*ret;

	start = 0;
	i = 0;
	if (!s1)
		return (0);
	if (!set)
		return ((char *) s1);
	end = ft_strlen(s1) - 1;
	while (s1[start] && check_in(s1[start], set))
		start++;
	while (s1[end] && check_in(s1[end], set) && start <= end)
		end--;
	ret = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!ret)
		return (0);
	while (start <= end)
		ret[i++] = s1[start++];
	ret[i] = '\0';
	return (ret);
}
