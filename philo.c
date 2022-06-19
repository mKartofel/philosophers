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

int main(int argc, char **argv)
{
	t_params params;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	get_params(argc, argv, &params);
}