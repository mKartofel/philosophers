/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo->c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student->42->fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:30:44 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/19 17:41:38 by vfiszbin         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void get_params(int argc, char **argv, t_params *params)
{
	params->nb_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->nb_must_eat = ft_atoi(argv[5]);
	else 
		params->nb_must_eat = 0;
}

void free_philos(t_params *params, t_philo *philos)
{
	int i;

	i = 0;
	while (i < params->nb_philo)
	{
		pthread_mutex_destroy(&(philos[i].right_fork));
		i++;
	}
	free(philos);
}

void wait_for_threads(t_params *params, t_philo *philos)
{
	int i;

	i = 0;
	while (i < params->nb_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

t_philo *create_philos(t_params *params)
{
	t_philo *philos;
	int i;
	int j;

	philos = malloc(sizeof(t_philo) * params->nb_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < params->nb_philo)
	{
		philos[i].num = i + 1;
		philos[i].state = 1;
		philos[i].params = params;
		if (pthread_mutex_init(&(philos[i].right_fork), NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&(philos[i].right_fork));
				j++;
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

void *routine(void *philos_arg)
{
	t_philo *philos;

	philos = (t_philo *)philos_arg;
	printf("HIHI je suis num %d\n", philos->num);
	return (NULL);
}

int start_threads(t_params *params, t_philo *philos)
{
	int i;

	i = 0;
	while (i < params->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &(philos[i])) != 0)
			return (1); //handle error
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_params params;
	t_philo *philos;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	get_params(argc, argv, &params);
	philos = create_philos(&params);
	if (!philos)
		return (1);
	start_threads(&params, philos);
	wait_for_threads(&params, philos);
	free_philos(&params, philos);
}