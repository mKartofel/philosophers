/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:58:18 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/22 13:37:13 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_params(int argc, char **argv, t_params *params)
{
	params->end = 0;
	params->nb_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (params->nb_philo < 1 || params->time_to_die < 0
		|| params->time_to_eat < 0 || params->time_to_sleep < 0)
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

void	free_philos(t_params *params, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < params->nb_philo)
	{
		pthread_mutex_destroy(philos[i].right_fork);
		free(philos[i].right_fork);
		pthread_mutex_destroy(philos[i].check_death);
		free(philos[i].check_death);
		i++;
	}
	pthread_mutex_destroy(&params->display);
	free(philos);
}

void	wait_for_threads(t_params *params, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < params->nb_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	start_threads(t_params *params, t_philo *philos)
{
	int	i;

	i = 0;
	// while (i < params->nb_philo)
	// {
	// 	philos[i].time_last_meal = get_time();
	// 	if (pthread_create(&philos[i].thread, NULL,
	// 			&routine, &(philos[i])) != 0)
	// 		return (1);
	while (i < params->nb_philo)
	{
		philos[i].time_last_meal = get_time();
		if (pthread_create(&philos[i].thread, NULL,
			&routine, &(philos[i])) != 0)
		return (1);
		i += 2;
	}
	i = 1;
	usleep(15000);
	while (i < params->nb_philo)
	{
		philos[i].time_last_meal = get_time();
		if (pthread_create(&philos[i].thread, NULL,
			&routine, &(philos[i])) != 0)
		return (1);
		i += 2;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philos;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	if (get_params(argc, argv, &params) == 1)
		return (1);
	philos = create_philos(&params);
	if (!philos)
		return (1);
	if (start_threads(&params, philos) == 1)
		params.end = 1;
	else
		check_end(&params, philos);
	wait_for_threads(&params, philos);
	free_philos(&params, philos);
}
