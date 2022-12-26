/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:45:01 by joushin           #+#    #+#             */
/*   Updated: 2022/12/26 19:24:24 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>

typedef struct s_init_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				is_dead;
	long			tv_sec;
	int				tv_usec;
	char			*shared_fork;
	pthread_mutex_t	*time_mutex;
	pthread_mutex_t	**fork_mutex;
}t_init_data;

typedef struct s_each_philo
{
	int				is_full;
	int				last_eat;
	int				id;
	int				eat_count;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	is_full_mutex;
	t_init_data		*init_data;
}t_each_philo;

int		ft_atoi(const char *str);

void	sleeping(t_each_philo *philo);
void	putdown_fork(t_each_philo *philo);
void	eating(t_each_philo *philo);
void	take_fork(t_each_philo *philo);

void	print_taken_a_fork(t_init_data *data, int philo_num);
void	print_eating(t_init_data *data, t_each_philo *philo);
void	print_sleeping(t_init_data *data, int philo_num);
void	print_thinking(t_init_data *data, int philo_num);
void	print_died(t_init_data *data, int philo_num);

int		get_time(t_init_data *data);
void	monitoring(t_init_data *data, t_each_philo *each_philo);
void	msleep(int time);

void	clean(t_each_philo *each_philo, t_init_data *data);

#endif
