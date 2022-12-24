/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:52:02 by joushin           #+#    #+#             */
/*   Updated: 2022/12/24 21:47:11 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_taken_a_fork(t_init_data *data, int philo_num)
{
	int	time_stamp;

	pthread_mutex_lock(data->time_mutex);
	time_stamp = get_time(data);
	printf("%d %d has taken a fork\n", time_stamp, philo_num);
	pthread_mutex_unlock(data->time_mutex);
}

void	print_eating(t_init_data *data, t_each_philo *philo)
{
	int	time_stamp;

	pthread_mutex_lock(&(philo->last_eat_mutex));
	pthread_mutex_lock(data->time_mutex);
	time_stamp = get_time(data);
	philo->last_eat = time_stamp;
	pthread_mutex_unlock(&(philo->last_eat_mutex));
	printf("%d %d is eating\n", time_stamp, philo->id);
	pthread_mutex_unlock(data->time_mutex);
}

void	print_sleeping(t_init_data *data, int philo_num)
{
	int	time_stamp;

	pthread_mutex_lock(data->time_mutex);
	time_stamp = get_time(data);
	printf("%d %d is sleeping\n", time_stamp, philo_num);
	pthread_mutex_unlock(data->time_mutex);
}

void	print_thinking(t_init_data *data, int philo_num)
{
	int	time_stamp;

	pthread_mutex_lock(data->time_mutex);
	time_stamp = get_time(data);
	printf("%d %d is thinking\n", time_stamp, philo_num);
	pthread_mutex_unlock(data->time_mutex);
}

void	print_died(t_init_data *data, int philo_num)
{
	int	time_stamp;

	pthread_mutex_lock(data->time_mutex);
	time_stamp = get_time(data);
	printf("%d %d is died\n", time_stamp, philo_num);
	pthread_mutex_unlock(data->time_mutex);
}
