/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:52:02 by joushin           #+#    #+#             */
/*   Updated: 2022/12/23 18:10:47 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_taken_a_fork(int time_stamp, int philo_num)
{
	printf("%d %d has taken a fork\n", time_stamp, philo_num);
}

void	print_eating(int time_stamp, int philo_num)
{
	printf("%d %d is eating\n", time_stamp, philo_num);
}

void	print_sleeping(int time_stamp, int philo_num)
{
	printf("%d %d is sleeping\n", time_stamp, philo_num);
}

void	print_thinking(int time_stamp, int philo_num)
{
	printf("%d %d is thinking\n", time_stamp, philo_num);
}

void	print_died(int time_stamp, int philo_num)
{
	printf("%d %d is died\n", time_stamp, philo_num);
}
