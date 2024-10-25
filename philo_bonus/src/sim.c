/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:46:00 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/25 14:30:48 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	get_child_status(t_table *table, pid_t pid)
{
	int	philo_exit_status;
	int	status;

	if (waitpid(pid, &philo_exit_status, WNOHANG) == 0)
		return (0);
	if (WIFEXITED(philo_exit_status))
	{
		status = WEXITSTATUS(philo_exit_status);
		if (status == EXIT_PHILO_DEAD || status == 1)
			return (kill_philos(table), 1);
		if (status == EXIT_PHILO_FULL)
		{
			table->philos_full++;
			return (1);
		}
	}
	return (0);
}

static int	create_end_monitors(t_table *table)
{
	if (pthread_create(&table->global_death_monitor, NULL,
			&global_death_monitor, table) != 0)
		return (1);
	if (pthread_create(&table->global_eat_monitor, NULL,
			&global_eat_monitor, table) != 0)
		return (1);
	return (0);
}

bool	sim_ended(t_table *table)
{
	bool	status;

	sem_wait(table->sem_sim_end);
	status = table->sim_end;
	sem_post(table->sem_sim_end);
	return (status);
}

int	start_sim(t_table *table)
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
	if (create_end_monitors(table) != 0)
		return (1);
	return (0);
}

int	stop_sim(t_table *table)
{
	int	i;
	int	child_status;

	sim_start_wait(table->start_time);
	while (sim_ended(table) == false)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			child_status = get_child_status(table, table->pids[i]);
			if (child_status == 1 || child_status == 2)
			{
				sem_wait(table->sem_sim_end);
				table->sim_end = true;
				sem_post(table->sem_philo_full);
				sem_post(table->sem_philo_dead);
				sem_post(table->sem_sim_end);
				return (child_status);
			}
			i++;
		}
	}
	pthread_join(table->global_death_monitor, NULL);
	pthread_join(table->global_eat_monitor, NULL);
	return (0);
}
