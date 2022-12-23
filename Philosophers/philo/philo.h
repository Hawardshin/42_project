/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:45:01 by joushin           #+#    #+#             */
/*   Updated: 2022/12/23 21:29:33 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_init_data
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat; //opt default = -1
	long	tv_sec; //second
	long	tv_usec;//micro second
	char	*shared_fork;
}t_init_data;


typedef struct s_each_philo
{
	t_init_data		*init_data;
	int				philo_id;
	int				philo_time;
	int				is_die;
}t_each_philo;

int	ft_atoi(const char *str);

#endif
