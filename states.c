/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:56:10 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/21 12:47:07 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	display_state(philo, "has taken a fork", 0);
	if (philo->left_fork != NULL)
	{
		pthread_mutex_lock(philo->left_fork);
		display_state(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->check_death);
		display_state(philo, "is eating", 0);
		philo->time_last_meal = get_time();
		pthread_mutex_unlock(philo->check_death);
		philo->nb_meals++;
		if (philo->params->end == 0)
			micro_sleeps(philo, philo->params->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
		pthread_mutex_unlock(philo->right_fork);
}

void	sleep_philo(t_philo *philo)
{
	display_state(philo, "is sleeping", 0);
	if (philo->params->end == 0)
		micro_sleeps(philo, philo->params->time_to_sleep);
}

void	think_philo(t_philo *philo)
{
	display_state(philo, "is thinking", 0);
}

void	display_state(t_philo *philo, char *msg, int death)
{
	struct timeval	time;

	pthread_mutex_lock(philo->display);
	if (philo->params->end == 0 || death == 1)
	{
		gettimeofday(&time, NULL);
		printf("%ld %d %s\n", ((time.tv_sec * 1000) + (time.tv_usec / 1000))
			- philo->start_time, philo->num, msg);
	}
	pthread_mutex_unlock(philo->display);
}

void	*routine(void *philo_arg)
{
	t_philo	*philo;
	// long	offset_time;

	philo = (t_philo *)philo_arg;
	// if ((philo->num % 2) == 0)
	// {
	// 	offset_time = 30 - (get_time() - philo->start_time);
	// 	printf("\noffset_time = %ld\n", offset_time);
	// 	if (offset_time > 0)
	// 		micro_sleeps(philo, offset_time);
	// }
	while (philo->params->end == 0)
	{
		eat_philo(philo);
		if (philo->params->end != 0)
			break ;
		sleep_philo(philo);
		if (philo->params->end != 0)
			break ;
		think_philo(philo);
	}
	return (NULL);
}
