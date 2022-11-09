/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:26:25 by joushin           #+#    #+#             */
/*   Updated: 2022/11/09 22:25:49 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./include/node.h"

static long long	len_count(char const *str, char c)
{
	long long	count;
	long long	i;

	count = 0;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		while (str[i] && str[i] != c)
			i++;
		count++;
		while (str[i] && str[i] == c)
			i++;
	}
	return (count);
}

static long long	len_into(char const *str, char c)
{
	long long	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static void	move_if_charset(const char **str, char c)
{
	while (**str && **str == c)
		(*str)++;
}

char	**ft_msplit(char const *str, char c)
{
	char		**result;
	long long	i;
	long long	k;

	i = 0;
	if (!str)
		print_error(0, NULL);
	result = (char **)malloc(sizeof(char *) * (len_count(str, c) + 1));
	if (!result)
		print_error(0, NULL);
	move_if_charset(&str, c);
	while (*str)
	{
		k = 0;
		result[i] = malloc(sizeof(char) * (len_into(str, c) + 1));
		if (!result[i])
			print_error(0, NULL);
		while (*str && *str != c)
			result[i][k++] = *str++;
		result[i][k] = '\0';
		i++;
		move_if_charset(&str, c);
	}
	result[i] = 0;
	return (result);
}
