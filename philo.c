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

void display_state(t_philo *philo, char *msg)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	printf("%ld %d %s\n", ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - philo->start_time, philo->num, msg);
}

void *routine(void *philo_arg)
{
	t_philo *philo;

	philo = (t_philo *)philo_arg;
	printf("HIHI je suis num %d\n", philo->num);
	usleep(1000000);
	display_state(philo, "is thinking");
	return (NULL);
}

int start_threads(t_params *params, t_philo *philos)
{
	int i;
	struct timeval time;
	long long start_time;

	gettimeofday(&time, NULL);
	start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	i = 0;
	while (i < params->nb_philo)
	{
		philos[i].start_time = start_time;
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