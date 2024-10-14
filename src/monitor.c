/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:22:16 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/14 15:37:37 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	sim_stopped(t_table *table)
{
	bool	end;

	end = false;
	pthread_mutex_lock(&table->sim_end_lock);
	if (table->sim_end == true)
		end = true;
	pthread_mutex_unlock(&table->sim_end_lock);
	return (end);
}

void	set_sim_status(t_table *table, bool status)
{
	pthread_mutex_lock(&table->sim_end_lock);
	table->sim_end = status;
	pthread_mutex_unlock(&table->sim_end_lock);
}

bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		set_sim_status(philo->table, true);
		print_status(philo, "died", true);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

bool	end_condition(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->philos[i].meal_time_lock);
		if (kill_philo(&table->philos[i]) == true)
			return (true);
		// if (table->min_eat_count != -1 && table->philos[i]->times->ate < table->min_eat_count)
		pthread_mutex_unlock(&table->philos[i].meal_time_lock);
		i++;
	}
	return (false);
}

void	*death_monitor(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->min_eat_count == 0)
		return (NULL);
	set_sim_status(table, false);
	while (get_time_in_ms() < table->start_time)
		continue ;
	while (1)
	{
		if (end_condition(table) == true)
			return (NULL);
		usleep(5000);
	}
	return (NULL);
}
