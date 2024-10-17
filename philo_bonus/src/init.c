/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:14:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/17 14:18:39 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

int	init_table(t_table *table, int ac, char **av)
{
	int	i;

	i = 1;
	memset(table, 0, sizeof(t_table));
	table->nb_philo = philo_atoi(av[i++]);
	table->time_to_die = philo_atoi(av[i++]);
	table->time_to_eat = philo_atoi(av[i++]);
	table->time_to_sleep = philo_atoi(av[i++]);
	table->must_eat_count = -1;
	if (ac == 6)
		table->must_eat_count = philo_atoi(av[i++]);
	return (0);
}
