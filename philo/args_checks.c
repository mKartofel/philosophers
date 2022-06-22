/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:16:23 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/22 16:52:24 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Computes the length of the string str, returns the number of characters
that precede the terminating NUL character*/
size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

/*Tests for a decimal digit character (between 0 and 9)*/
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*Check if arg is a number*/
int	arg_is_digit(char *arg)
{
	int	i;

	if (arg[0] != '-' && !ft_isdigit(arg[0]))
		return (0);
	i = 1;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Converts the initial portion of the string pointed to by nptr
 *	to long representation
 * 
 * @param nptr 
 * @return long 
 */
long	ft_atol(const char *nptr)
{
	int		i;
	long	num;
	int		sign;

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

/*Check if the argument is a valid C integer that does not overflow/underflow*/
int	arg_is_int(char *arg)
{
	long	num;

	if (ft_strlen(arg) > 10)
		return (0);
	num = ft_atol(arg);
	if (num <= 2147483647 && num >= -2147483648)
		return (1);
	return (0);
}	
