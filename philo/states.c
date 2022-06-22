/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:56:10 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/22 11:52:39 by vfiszbin         ###   ########.fr       */
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
		pthread_mutex_lock(&philo->params->check_meals);
		philo->nb_meals++;
		pthread_mutex_unlock(&philo->params->check_meals);
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
	micro_sleeps(philo, philo->params->time_to_sleep);
}

void	think_philo(t_philo *philo)
{
	display_state(philo, "is thinking", 0);
}

void	display_state(t_philo *philo, char *msg, int death)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->params->display);
	pthread_mutex_lock(&philo->params->end_check);
	if (philo->params->end == 0 || death == 1)
	{
		pthread_mutex_unlock(&philo->params->end_check);
		gettimeofday(&time, NULL);
		printf("%ld %d %s\n", ((time.tv_sec * 1000) + (time.tv_usec / 1000))
			- philo->start_time, philo->num, msg);
	}
	else
		pthread_mutex_unlock(&philo->params->end_check);
	pthread_mutex_unlock(&philo->params->display);
}

void	*routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	if ((philo->num % 2) == 0)
		usleep(30000);
	while (1)
	{
		pthread_mutex_lock(&philo->params->end_check);
		if (philo->params->end != 0)
		{
			pthread_mutex_unlock(&philo->params->end_check);
			break ;
		}
		pthread_mutex_unlock(&philo->params->end_check);
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return (NULL);
}
