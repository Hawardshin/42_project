/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 07:35:17 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 11:35:57 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	len_count(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static int	len_into(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	**all_free(int i, char **result)
{
	while (--i >= 0)
	{
		free(result[i]);
		result[i] = NULL;
	}
	free(result);
	result = NULL;
	return (0);
}

char	**ft_split(char const *str, char c)
{
	char	**result;
	int		i;
	int		k;

	i = 0;
	result = (char **)malloc(sizeof(char *) * (len_count(str, c) + 1));
	if (!result)
		return (0);
	while (*str && *str == c)
		str++;
	while (*str)
	{
		k = 0;
		result[i] = malloc(sizeof(char) * (len_into(str, c) + 1));
		if (!result[i])
			return (all_free(i, result));
		while (*str && *str != c)
			result[i][k++] = *str++;
		result[i][k] = '\0';
		i++;
		while (*str && *str == c)
			str++;
	}
	result[i] = 0;
	return (result);
}
