/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params_and_philos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:04:05 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/20 19:15:23 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_params(int argc, char **argv, t_params *params)
{
	params->end = 0;
	params->nb_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (params->nb_philo < 1 || params->time_to_die < 0 || params->time_to_eat < 0
		|| params->time_to_sleep < 0)
		{
			printf("Incorrect arguments\n");
			return (1);
		}
	if (argc == 6)
	{
		params->nb_must_eat = ft_atoi(argv[5]);
		if (params->nb_must_eat < 0)
		{
			printf("Incorrect arguments\n");
			return (1);
		}
	}
	else 
		params->nb_must_eat = -1;
	return (0);
}

t_philo *create_philos(t_params *params)
{
	t_philo *philos;
	int i;
	int j;
	int ret1;
	int ret2;
	long start_time;

	philos = malloc(sizeof(t_philo) * params->nb_philo);
	if (!philos)
		return (NULL);
	if (pthread_mutex_init(&(params->display), NULL) != 0)
	{
		free(philos);
		return (NULL);
	}
	start_time = get_time();
	i = 0;
	ret1 = 0;
	ret2 = 0;
	while (i < params->nb_philo)
	{
		philos[i].num = i + 1;
		philos[i].state = 1;
		philos[i].params = params;
		philos[i].display = &(params->display);
		philos[i].start_time = start_time;
		philos[i].time_last_meal = start_time;
		philos[i].nb_meals = 0;
		philos[i].right_fork = malloc(sizeof(pthread_mutex_t));
		if (!philos[i].right_fork)
		{
			free(philos);
			return (NULL);
		}
		philos[i].left_fork = NULL;
		philos[i].check_death = malloc(sizeof(pthread_mutex_t));
		if (!philos[i].check_death)
		{
			free(philos);
			free(philos[i].right_fork);
			return (NULL);
		}
		ret1 = pthread_mutex_init(philos[i].right_fork, NULL);
		ret2 = pthread_mutex_init(philos[i].check_death, NULL);
		if ( ret1 != 0 ||  ret2 != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(philos[j].right_fork);
				free(philos[j].right_fork);
				pthread_mutex_destroy(philos[j].check_death);
				free(philos[j].check_death);
				j++;
			}
			if (ret2 != 0)
			{
				pthread_mutex_destroy(philos[j].right_fork);
				free(philos[j].right_fork);
			}
			free(philos);
			return (NULL);
		}
		if (i > 0)
		{
			philos[i].left_fork = philos[i - 1].right_fork;
			if (i == params->nb_philo - 1)
			{
				philos[0].left_fork = philos[i].right_fork;
			}
		}
		i++;
	}
	return (philos);
}