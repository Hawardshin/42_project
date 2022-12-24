/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:20:38 by joushin           #+#    #+#             */
/*   Updated: 2022/12/24 16:56:39 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 죽어야 하는 시간이 0인 경우 바로 죽이기.
//먹는 시간이 0인 경우는 의미 없음
// 반드시 먹어야하는게 0이라면 바로 종료 할 수 있도록 코드 짜기. 기본 init 은 -1로 처리

int	get_time(t_init_data *data)
{
	struct timeval	now_time;
	long			sec;
	int				usec;

	pthread_mutex_lock(data->time_mutex);
	gettimeofday(&now_time, NULL);
	sec = now_time.tv_sec;
	usec = now_time.tv_usec;
	pthread_mutex_unlock(data->time_mutex);
	return ((sec - data->tv_sec) * 1000 + ((usec - data->tv_usec) / 1000));
}

void	*philo_main(void *param)
{
	t_each_philo	*each_philo;
	t_init_data		*data;

	each_philo = (t_each_philo *)param;
	data = each_philo->init_data;
	if (each_philo->id % 2 == 0)
		msleep(data->time_to_eat);
	while (1)
	{
		if (each_philo ->eat_count == data->must_eat)
			each_philo->is_full = 1;
		take_fork(each_philo);
		eating(each_philo);
		putdown_fork(each_philo);
		sleeping(each_philo);
		print_thinking(get_time(data), each_philo->id);
	}
	return (NULL);
}

int	init_input(int argc, char **argv, t_init_data *data)
{
	struct timeval	startTime;

	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	gettimeofday(&startTime, NULL);
	data->tv_sec = startTime.tv_sec;
	data->tv_usec = startTime.tv_usec;
	if (argc == 5)
		data->must_eat = -1;
	else
		data->must_eat = ft_atoi(argv[5]);
	if (data->num_of_philo <= 0 || data->time_to_die < 0 || \
	data->time_to_eat <= 0 || data->time_to_sleep <= 0 || data->must_eat < -1)
		return (1);
	return (0);
}

int	start_init(int argc, char **argv, t_init_data *data)
{
	int	i;

	i = 0;
	if (init_input(argc, argv, data))
		return (1);
	data->shared_fork = malloc(sizeof(char) * data->num_of_philo);
	data->fork_mutex = malloc(sizeof(pthread_mutex_t *) * data->num_of_philo);
	data->time_mutex = malloc (sizeof(pthread_mutex_t));
	data->last_eat_mutex = malloc (sizeof(pthread_mutex_t));
	pthread_mutex_init(data->time_mutex, NULL);
	pthread_mutex_init(data->last_eat_mutex, NULL);
	while (i < data->num_of_philo)
	{
		data->fork_mutex[i] = malloc (sizeof (pthread_mutex_t));
		pthread_mutex_init(data->fork_mutex[i], NULL);
		i++;
	}
	return (0);
}

void	sitdown(t_init_data *data, t_each_philo *philo, pthread_t *philo_arr)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].init_data = data;
		philo[i].id = i + 1;
		philo[i].last_eat = get_time(data);
		philo[i].eat_count = 0;
		pthread_create(&(philo_arr[i]), NULL, philo_main, (void *) &philo[i]);
		pthread_detach(philo_arr[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_init_data		*data;
	t_each_philo	*each_philo;
	pthread_t		*philo_arr;

	data = malloc (sizeof (t_init_data));
	memset(data, 0, sizeof (t_init_data));
	if ((argc != 5 && argc != 6) || start_init(argc, argv, data))
		return (1);
	philo_arr = malloc (sizeof(pthread_t) * (data->num_of_philo));
	each_philo = malloc (sizeof(t_each_philo) * (data->num_of_philo));
	if (!philo_arr || !each_philo)
	{
		free(philo_arr);
		free(each_philo);
		return (1);
	}
	sitdown(data, each_philo, philo_arr);
	monitoring(data, each_philo);

}
