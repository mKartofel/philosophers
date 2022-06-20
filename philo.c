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


void free_philos(t_params *params, t_philo *philos)
{
	int i;

	i = 0;
	while (i < params->nb_philo)
	{
		pthread_mutex_destroy(philos[i].right_fork);
		free(philos[i].right_fork);
		pthread_mutex_destroy(philos[i].check_death);
		free(philos[i].check_death);
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

void check_end(t_params *params, t_philo *philos)
{
	int i;
	int must_eat_satisfied;


	while (params->end == 0)
	{
		i = 0;
		must_eat_satisfied = 1;
		while (i < params->nb_philo)
		{
			if (philos[i].nb_meals < params->nb_must_eat)
				must_eat_satisfied = 0;

			if (philos[i].time_last_meal - get_time() > params->time_to_die)
			{
				params->end = 1;
				display_state(&philos[i], "died");
				break;
			}
			i++;
		}
		if (params->end != 0 && must_eat_satisfied == 1)
		{
			params->end = 1;
			pthread_mutex_lock(&params->display);
			printf("Every philosopher have eaten a sufficient number of meals !\n");
			pthread_mutex_unlock(&params->display);
			break;
		}
		usleep(50);
	}
}


void display_state(t_philo *philo, char *msg)
{
	struct timeval time;

	pthread_mutex_lock(philo->display);
	gettimeofday(&time, NULL);
	printf("%ld %d %s\n", ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - philo->start_time, philo->num, msg);
	pthread_mutex_unlock(philo->display);
}

void *routine(void *philo_arg)
{
	t_philo *philo;

	philo = (t_philo *)philo_arg;
	printf("HIHI je suis num %d\n", philo->num);
	eat(philo);
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
	check_end(&params, philos);
	wait_for_threads(&params, philos);
	free_philos(&params, philos);
}