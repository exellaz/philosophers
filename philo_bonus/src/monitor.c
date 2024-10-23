/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:41:12 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/23 15:47:13 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	sim_ended(t_table *table)
{
	bool	status;

	sem_wait(table->sem_sim_end);
	status = table->sim_end;
	sem_post(table->sem_sim_end);
	return (status);
}

void	kill_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		kill(table->pids[i], SIGTERM);
		i++;
	}
}

void	*global_eat_monitor(void *data)
{
	t_table *table;

	table = (t_table *)data;
	if (table->must_eat_count < 0 || table->time_to_die == 0 || table->nb_philo == 1)
		return (NULL);
	sim_start_wait(table->start_time);
		// printf("Must eat count: %d\n", table->must_eat_count);
	while (table->philos_full < table->nb_philo)
	{
		if (sim_ended(table) == true)
			return (NULL);
		sem_wait(table->sem_philo_full);
		if (sim_ended(table) == false)
			table->philos_full++;
		else
			return (NULL);
	}
	sem_wait(table->sem_sim_end);
	table->sim_end = true;
	kill_philos(table);
	sem_post(table->sem_philo_dead);
	sem_post(table->sem_sim_end);
	return (NULL);
}

void	*global_monitor(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	sim_start_wait(table->start_time);
	if (sim_ended(table) == true)
		return (NULL);
	sem_wait(table->sem_philo_dead);
	if (sim_ended(table) == true)
		return (NULL);
	sem_wait(table->sem_sim_end);
	table->sim_end = true;
	kill_philos(table);
	sem_post(table->sem_philo_full);
	sem_post(table->sem_sim_end);
	return (NULL);
}

int	start_death_monitor(t_table *table)
{
	(void)table;
	return (0);
}

static bool	end_condition(t_table *table, t_philo *philo)
{
	time_t	current_time;

	current_time = get_time_in_ms();
	sem_wait(philo->sem_eat);
	if ((current_time - philo->last_meal) >= table->time_to_die)
	{
		print_status(philo, "died", true);
		sem_post(philo->sem_philo_dead);
		sem_post(philo->sem_eat);
		return (true);
	}
	if (table->must_eat_count != -1 && philo->ate_enough == false && philo->eat_count >= table->must_eat_count)
	{
		// printf("Eat Count: (%d)\n", philo->eat_count);
		sem_post(philo->sem_philo_full);
		philo->ate_enough = true;
	}
	sem_post(philo->sem_eat);
	return (false);
}

void	*local_monitor(void *data)
{
	t_table *table;

	table = (t_table *)data;
	if (table->must_eat_count == 0)
		return (NULL);
	sem_wait(table->current_philo.sem_philo_dead);
	sem_wait(table->current_philo.sem_philo_full);
	sim_start_wait(table->start_time);
	while (end_condition(table, &table->current_philo) == false)
	{
		usleep(100);
		continue ;
	}
	return (NULL);
}
