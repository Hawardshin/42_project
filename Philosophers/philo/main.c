/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:20:38 by joushin           #+#    #+#             */
/*   Updated: 2022/12/23 21:42:00 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 죽어야 하는 시간이 0인 경우 바로 죽이기.
//먹는 시간이 0인 경우는 의미 없음
// 반드시 먹어야하는게 0이라면 바로 종료 할 수 있도록 코드 짜기. 기본 init 은 -1로 처리

int	get_time(t_init_data *data)
{
	struct timeval	now_time;
	int				sec;
	int				usec;

	gettimeofday(&now_time, NULL);
	sec = now_time.tv_sec;
	usec = now_time.tv_usec;
	return ((sec - data->tv_sec) * 1000 + ((usec - data->tv_usec) / 1000));
}

void	*philo(void *param)
{
	t_each_philo	*each_philo;
	t_init_data		*data;

	each_philo = (t_each_philo *)param;
	data = each_philo->init_data;
	if (each_philo->philo_id % 2 == 0)
		usleep(data->time_to_eat * 1000);
	while (data->must_eat == -2 || data->must_eat)
	{
		take_left_fork(each_philo);
		take_right_fork(each_philo);
		eating(each_philo);
		putdown_right(each_philo);
		putdown_left(each_philo);
		sleeping(each_philo);
		print_thinking(get_time(data), each_philo->philo_id);
	}
}

int	start_init(int argc, char **argv, t_init_data *data)
{
	struct timeval	startTime;

	data->number_of_philosophers = ft_atoi(argv[1]);
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
	if (data->number_of_philosophers <= 0 || data->time_to_die < 0 || \
	data->time_to_eat <= 0 || data->time_to_sleep <= 0 || data->must_eat < -1)
		return (1);
	data->shared_fork = malloc(sizeof(char) * data->number_of_philosophers);
	return (0);
}

int	main(int argc, char **argv)
{
	t_init_data		*data;
	t_each_philo	*each_philo;
	pthread_t		*philo_arr;
	int				i;

	i = 0;
	if ((argc != 5 && argc != 6) || start_init(argc, argv, data))
		return (1);
	philo_arr = malloc (sizeof(pthread_t) * (data->number_of_philosophers));
	if (!philo_arr)
		return (1);
	each_philo = malloc (sizeof(t_each_philo) * (data->number_of_philosophers));
	if (!each_philo)
		return (1);
	while (i < data->number_of_philosophers)
	{
		each_philo[i].init_data = data;
		each_philo[i].philo_id = i;
		pthread_create(&(philo_arr[i]), NULL, philo, (void *) &each_philo[i]);
		i++;
	}
}
