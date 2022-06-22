/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:35:29 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/22 16:35:18 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Converts the initial portion of the string pointed to by nptr
 *	to int representation
 * 
 * @param nptr 
 * @return int 
 */
int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;
	int	sign;

	sign = 1;
	num = 0;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\r'
		|| nptr[i] == '\f' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	return (num * sign);
}

/**
 * @brief Get the current time in milliseconds
 * 
 * @return long current time (ms)
 */
long	get_time(void)
{
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time);
}

/**
 * @brief Put the calling thread to sleep for a certain amount of time
 * through repeated micro sleeps. The sleep ends if the simulation is over
 * @param philo 
 * @param sleep_duration Duration of sleep in milliseconds
 */
void	micro_sleeps(t_philo *philo, long sleep_duration)
{
	long	sleep_start;

	sleep_start = get_time();
	while (1)
	{
		pthread_mutex_lock(&philo->params->end_check);
		if (philo->params->end != 0)
		{
			pthread_mutex_unlock(&philo->params->end_check);
			break ;
		}	
		pthread_mutex_unlock(&philo->params->end_check);	
		if (get_time() - sleep_start >= sleep_duration)
			break ;
		usleep(100);
	}
}

int error_msg(char *msg, int ret)
{
	printf("%s\n", msg);
	return (ret);
}
