/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:24:32 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/13 13:04:49 by kkhai-ki         ###   ########.fr       */
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

void	philo_sleep(t_table *table, time_t sleep_time)
{
	time_t	wake_up;

	(void)table;
	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
		usleep(100);
}

void	*single_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork[0]]);
	print_status(philo, "has taken a fork");
	philo_sleep(philo->table, philo->table->time_to_die);
	print_status(philo, "has died");
	pthread_mutex_unlock(&philo->table->forks[philo->fork[1]]);
	return (NULL);
}

void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork[0]]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[philo->fork[1]]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_sleep(philo->table, philo->table->time_to_eat);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_time_lock);
	print_status(philo, "is sleeping");
	pthread_mutex_unlock(&philo->table->forks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork[0]]);
	philo_sleep(philo->table, philo->table->time_to_sleep);
}

void	think_routine(t_philo *philo, bool initial)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	// time_to_think = philo->table->time_to_die - (get_time_in_ms() - philo->last_meal) - philo->table->time_to_eat;
	time_to_think = (philo->table->time_to_die - (get_time_in_ms() - philo->last_meal) - philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (initial == false)
		print_status(philo, "is thinking");
	philo_sleep(philo->table, time_to_think);
}

void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		philo->id + 1, str);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
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
	else if (philo->id % 2)
		think_routine(philo, true);
	while (1)
	{
		eat_sleep_routine(philo);
		think_routine(philo, false);
	}
	return (NULL);
}
