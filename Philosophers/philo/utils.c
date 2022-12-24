/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:31:47 by joushin           #+#    #+#             */
/*   Updated: 2022/12/24 16:47:46 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					is_char;
	int					sign;
	unsigned long long	result;

	sign = 1;
	result = 0;
	is_char = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
		is_char = 0;
	}
	if (sign == -1 || is_char || result != (int)sign * result)
		return (-2);
	return ((int)sign * result);
}


void	msleep(int time)
{
	long				start_sec;
	int					start_usec;
	struct timeval	nt;
	int				cnt;

	gettimeofday(&nt, NULL);
	start_sec = nt.tv_sec;
	start_usec = nt.tv_usec;
	cnt = 0;
	while (cnt < time)
	{
		gettimeofday(&nt, NULL);
		cnt = (nt.tv_sec - start_sec) * 1000 + ((nt.tv_usec - start_usec) / 1000);
		usleep(100);
	}
}
