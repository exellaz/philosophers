/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:55:43 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/21 14:57:33 by kkhai-ki         ###   ########.fr       */
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
	// if (pthread_create(&table->global_monitor, NULL, &global_monitor, table))
	// 	return (1);
	return (0);
}

void	wait_for_sim(t_table *table)
{
	int	i;

	sim_start_wait(table->start_time);
	while (1)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			waitpid(table->pids[i], 0, WNOHANG);
			if (get_time_in_ms() == table->start_time + 10000)
				break ;
		}
	}
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
	wait_for_sim(&table);
	// pthread_join(table.global_monitor, NULL);
	return (0);
}
