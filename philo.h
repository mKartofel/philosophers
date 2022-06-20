/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:31:20 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/20 16:04:51 by vfiszbin         ###   ########.fr       */
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
	int end;
	int nb_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_must_eat;
	pthread_mutex_t display;
} t_params;

typedef struct s_philo
{
	int num;
	int state; //0 = eat, 1 = think, 2 = sleep
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *check_death;
	pthread_mutex_t *display;
	pthread_t	thread;
	t_params *params;
	long start_time;
	long time_last_meal;
	int nb_meals;
} t_philo;



int	ft_atoi(const char *nptr);
void display_state(t_philo *philo, char *msg);
long get_time(void);
void eat(t_philo *philo);
void get_params(int argc, char **argv, t_params *params);
t_philo *create_philos(t_params *params);

#endif