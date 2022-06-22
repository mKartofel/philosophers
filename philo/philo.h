/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:31:20 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/22 16:35:27 by vfiszbin         ###   ########.fr       */
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
	int				end;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	pthread_mutex_t	display;
	pthread_mutex_t	end_check;
	pthread_mutex_t	check_meals;
}	t_params;

typedef struct s_philo
{
	int				num;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*check_death;
	pthread_t		thread;
	t_params		*params;
	long			start_time;
	long			time_last_meal;
	int				nb_meals;
}	t_philo;

int		ft_atoi(const char *nptr);
void	display_state(t_philo *philo, char *msg, int death);
long	get_time(void);
void	eat_philo(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think_philo(t_philo *philo);
int		get_params(int argc, char **argv, t_params *params);
t_philo	*create_philos(t_params *params);
void	*routine(void *philo_arg);
void	check_end(t_params *params, t_philo *philos);
void	micro_sleeps(t_philo *philo, long sleep_duration);
int		arg_is_digit(char *arg);
int		arg_is_int(char *arg);
int		error_msg(char *msg, int ret);

#endif