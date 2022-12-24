/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:08:00 by joushin           #+#    #+#             */
/*   Updated: 2022/12/24 16:58:27 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_each_philo *philo)
{
	t_init_data	*data;

	data = philo->init_data;
	pthread_mutex_lock(data->fork_mutex[philo->id - 1]);
	data->shared_fork[philo->id - 1] = 1;
	print_taken_a_fork(get_time(data), philo->id);
	pthread_mutex_lock(data->fork_mutex[philo->id % data->num_of_philo]);
	data->shared_fork[philo->id % data->num_of_philo] = 1;
	print_taken_a_fork(get_time(data), philo->id);
}

void	eating(t_each_philo *philo)
{
	t_init_data	*data;
	int			time;

	data = philo->init_data;
	time = get_time(data);
	pthread_mutex_lock(data->last_eat_mutex);
	philo->last_eat = time;
	pthread_mutex_unlock(data->last_eat_mutex);
	print_eating(time, philo->id);
	msleep(data->time_to_eat);

}

void	putdown_fork(t_each_philo *philo)
{
	t_init_data	*data;

	data = philo->init_data;
	philo->eat_count++;
	data->shared_fork[philo->id % data->num_of_philo] = 0;
	pthread_mutex_unlock(data->fork_mutex[philo->id % data->num_of_philo]);
	data->shared_fork[philo->id - 1] = 0;
	pthread_mutex_unlock(data->fork_mutex[philo->id - 1]);
}

void	sleeping(t_each_philo *philo)
{
	print_sleeping(get_time(philo->init_data), philo->id);
	msleep(philo->init_data->time_to_sleep);
}
