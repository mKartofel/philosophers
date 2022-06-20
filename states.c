/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:56:10 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/20 15:58:34 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	display_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	display_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->check_death);
	display_state(philo, "is eating");
	philo->time_last_meal = get_time();
	philo->nb_meals++;
	pthread_mutex_unlock(philo->check_death);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}