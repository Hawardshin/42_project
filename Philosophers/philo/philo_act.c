/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:08:00 by joushin           #+#    #+#             */
/*   Updated: 2022/12/24 21:28:51 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_each_philo *philo)
{
	t_init_data	*data;

	data = philo->init_data;
	pthread_mutex_lock(data->fork_mutex[philo->id - 1]);
	data->shared_fork[philo->id - 1] = 1;
	print_taken_a_fork(data, philo->id);
	pthread_mutex_lock(data->fork_mutex[philo->id % data->num_of_philo]);
	data->shared_fork[philo->id % data->num_of_philo] = 1;
	print_taken_a_fork(data, philo->id);
}

void	eating(t_each_philo *philo)
{
	t_init_data	*data;

	data = philo->init_data;
	print_eating(data, philo);
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
	print_sleeping(philo->init_data, philo->id);
	msleep(philo->init_data->time_to_sleep);
}
