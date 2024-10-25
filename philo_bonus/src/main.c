/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:55:43 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/25 14:46:17 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	cleanup_table(t_table *table);

int	main(int ac, char *av[])
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (printf("Incorrect number of arguments\n"), 1);
	if (!is_valid_input(ac, av))
		return (1);
	if (init_table(&table, ac, av) != 0)
		return (cleanup_sem(&table), 1);
	start_sim(&table);
	stop_sim(&table);
	cleanup_table(&table);
	return (0);
}

static void	cleanup_table(t_table *table)
{
	int	i;

	i = 0;
	cleanup_sem(table);
	while (i < table->nb_philo)
	{
		if (table->philos[i].sem_eat_name != NULL)
			free(table->philos[i].sem_eat_name);
		pthread_detach(table->philos[i].local_monitor);
		i++;
	}
	free(table->philos);
	free(table->pids);
}
