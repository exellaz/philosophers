/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:39:38 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/09 20:03:00 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isdigit(char c)
{
	if (c < '0' || c > '9')
		return (false);
	return (true);
}

bool	is_only_digits(char *str)
{
	if (!str)
		return (false);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

int	philo_atoi(char *str)
{
	unsigned long	nbr;
	int				i;

	i = 0;
	nbr = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (nbr > INT_MAX)
		return (-1);
	return ((int)nbr);
}

bool	is_valid_input(int ac, char **av)
{
	int	i;
	int	nbr;

	i = 0;
	while (++i < ac)
	{
		if (!is_only_digits(av[i]))
			return (false);
		nbr = philo_atoi(av[i]);
		if (i == 1 && (nbr <= 0 || nbr > PHILO_MAX))
			return (false);
		if (i != 1 && nbr == -1)
			return (false);
	}
	return (true);
}
