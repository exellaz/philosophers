/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:51:02 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/09 20:27:43 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, int ac, char **av)
{
	int	i;

	i = 1;
	memset(&table, 0, sizeof(t_table));
	table->nb_philo = philo_atoi(av[i++]);
	table->time_to_die = philo_atoi(av[i++]);
	table->time_to_eat = philo_atoi(av[i++]);
	table->time_to_sleep = philo_atoi(av[i++]);
	table->min_eat_count = 0;
	if (ac == 6)
		table->min_eat_count = philo_atoi(av[i++]);
}

int	main(int ac, char *av[])
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (1);
	if (!is_valid_input(ac, av))
		return (EXIT_FAILURE);
	init_table(&table, ac, av);
}
