/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 14:15:51 by joushin           #+#    #+#             */
/*   Updated: 2022/12/26 17:59:20 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	anyone_die(t_init_data *data, t_each_philo *each_philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&(each_philo[i].last_eat_mutex));
		if (get_time(data) - each_philo[i].last_eat > data->time_to_die)
		{
			print_died(data, i + 1);
			return (1);
		}
		pthread_mutex_unlock(&(each_philo[i].last_eat_mutex));
		i++;
	}
	return (0);
}

int	everyone_full(t_init_data *data, t_each_philo *each_philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&(each_philo->is_full_mutex));
		if (each_philo[i].is_full != 1)
		{
			pthread_mutex_unlock(&(each_philo->is_full_mutex));
			return (0);
		}
		pthread_mutex_unlock(&(each_philo->is_full_mutex));
		i++;
	}
	return (1);
}

void	monitoring(t_init_data *data, t_each_philo *each_philo)
{
	while (1)
	{
		if (anyone_die(data, each_philo))
			return ;
		if (everyone_full(data, each_philo))
			return ;
	}
}
