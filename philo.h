/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:31:20 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/20 12:11:06 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_params
{
	int nb_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_must_eat;
} t_params;

typedef struct s_philo
{
	int num;
	int state; //0 = eat, 1 = think, 2 = sleep
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
	pthread_t	thread;
	t_params *params;
	long start_time;
} t_philo;



int	ft_atoi(const char *nptr);

#endif