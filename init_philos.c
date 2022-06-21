/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params_and_philos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:04:05 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/21 09:52:41 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*free_and_leave(t_philo	**philos, int i, int ret2)
{
	int		j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy((*philos)[j].right_fork);
		free((*philos)[j].right_fork);
		pthread_mutex_destroy((*philos)[j].check_death);
		free((*philos)[j].check_death);
		j++;
	}
	if (ret2 != 0)
	{
		pthread_mutex_destroy((*philos)[j].right_fork);
		free((*philos)[j].right_fork);
	}
	free(*philos);
	return (NULL);
}

int	init_philo(t_params *params, t_philo **philos, long start_time, int i)
{
	(*philos)[i].num = i + 1;
	(*philos)[i].params = params;
	(*philos)[i].display = &(params->display);
	(*philos)[i].start_time = start_time;
	(*philos)[i].time_last_meal = start_time;
	(*philos)[i].nb_meals = 0;
	(*philos)[i].right_fork = malloc(sizeof(pthread_mutex_t));
	if (!(*philos)[i].right_fork)
	{
		free(*philos);
		return (1);
	}
	(*philos)[i].left_fork = NULL;
	(*philos)[i].check_death = malloc(sizeof(pthread_mutex_t));
	if (!(*philos)[i].check_death)
	{
		free(*philos);
		free((*philos)[i].right_fork);
		return (1);
	}
	return (0);
}

void	set_left_fork(t_params *params, t_philo *philos, int i)
{
	if (i > 0)
	{
		philos[i].left_fork = philos[i - 1].right_fork;
		if (i == params->nb_philo - 1)
		{
			philos[0].left_fork = philos[i].right_fork;
		}
	}
}

int	init_vars(t_params *params, t_philo **philos)
{
	*philos = malloc(sizeof(t_philo) * params->nb_philo);
	if (!*philos)
		return (1);
	if (pthread_mutex_init(&(params->display), NULL) != 0)
	{
		free(*philos);
		return (1);
	}
	return (0);
}

t_philo	*create_philos(t_params *params)
{
	t_philo	*philos;
	int		i;
	int		ret1;
	int		ret2;
	long	start_time;

	if (init_vars(params, &philos) == 1)
		return (NULL);
	start_time = get_time();
	i = -1;
	ret1 = 0;
	ret2 = 0;
	while (++i < params->nb_philo)
	{
		if (init_philo(params, &philos, start_time, i) == 1)
			return (NULL);
		ret1 = pthread_mutex_init(philos[i].right_fork, NULL);
		ret2 = pthread_mutex_init(philos[i].check_death, NULL);
		if (ret1 != 0 || ret2 != 0)
			return (free_and_leave(&philos, i, ret2));
		set_left_fork(params, philos, i);
	}
	return (philos);
}
