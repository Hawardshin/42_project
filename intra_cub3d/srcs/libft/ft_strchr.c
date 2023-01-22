/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:10:31 by joushin           #+#    #+#             */
/*   Updated: 2022/07/12 12:20:55 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strchr(const char *str, int c)
{
	char	temp;
	int		idx;

	temp = (char)c;
	idx = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == temp)
			return (idx);
		idx++;
	}
	if (temp == '\0')
		return (idx);
	return (-1);
}
