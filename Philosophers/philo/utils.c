/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:31:47 by joushin           #+#    #+#             */
/*   Updated: 2022/12/26 20:33:12 by joushin          ###   ########.fr       */
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
	long				ssec;
	int					susec;
	struct timeval		nt;
	int					cnt;

	gettimeofday(&nt, NULL);
	ssec = nt.tv_sec;
	susec = nt.tv_usec;
	cnt = 0;
	while (cnt < time)
	{
		gettimeofday(&nt, NULL);
		cnt = (nt.tv_sec - ssec) * 1000 + ((nt.tv_usec - susec) / 1000);
		usleep(100);
	}
}

int	get_time(t_init_data *data)
{
	struct timeval	now_time;
	long			sec;
	int				usec;

	gettimeofday(&now_time, NULL);
	sec = now_time.tv_sec;
	usec = now_time.tv_usec;
	return ((sec - data->tv_sec) * 1000 + ((usec - data->tv_usec) / 1000));
}

void	clean(t_each_philo *each_philo, t_init_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&(each_philo[i].last_eat_mutex));
		pthread_mutex_destroy(&(each_philo[i].is_full_mutex));
		i++;
	}
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(data->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(data->time_mutex);
}
