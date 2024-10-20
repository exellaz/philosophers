/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:55:43 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/20 13:38:23 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

static int	start_sim(t_table *table)
{
	int		i;
	pid_t	pid;

	table->start_time = get_time_in_ms() + (table->nb_philo * 20);
	i = 0;
	while (i < table->nb_philo)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		else if (pid > 0)
			table->pids[i] = pid;
		else if (pid == 0)
		{
			table->current_philo = table->philos[i];
			philosopher(table);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (printf("Incorrect number of arguments\n"), 1);
	if (!is_valid_input(ac, av))
		return (1);
	if (init_table(&table, ac, av) != 0)
		return (cleanup_sem(&table), 1);
	cleanup_sem(&table);
	start_sim(&table);
	waitpid(table.pids[0], NULL, 0);
	return (0);
}
