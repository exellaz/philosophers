/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:24:32 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/11 16:37:19 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_sim(t_table *table)
{
	int	i;

	table->start_time = get_time_in_ms() + (table->nb_philo * 20);
	i = 0;
	while (i < table->nb_philo)
	{
		if(pthread_create(&table->philos[i].thread, NULL, &philosopher, &table->philos[i]) != 0)
			return (1);
		i++;
	}
		// printf("nb_philo: (%d)\n", table->nb_philo);
	pthread_join(table->philos[i - 1].thread, NULL);
	return (0);
}

time_t	get_time_in_ms(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sim_start_wait(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue ;
}

void	*single_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork[0]]);
	printf("%d has taken a fork\n", philo->id + 1);
	pthread_mutex_unlock(&philo->table->forks[philo->fork[1]]);
	return (NULL);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	printf("Here!\n");
	philo = (t_philo *)data;
	(void)data;
	if (philo->table->min_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_start_wait(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->nb_philo == 1)
		return (single_philo_routine(philo));
	return (NULL);
}

