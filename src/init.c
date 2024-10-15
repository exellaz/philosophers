/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:06:01 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/15 13:21:53 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!forks)
		return (NULL);
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

int	init_all_mutexes(t_table *table)
{
	table->forks = init_forks(table);
	if (!table->forks)
		return (1);
	if (pthread_mutex_init(&table->sim_end_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (1);
	return (0);
}

void	assign_forks(t_philo *philo, t_table *table, int nb_philo)
{
	philo->fork[0] = &table->forks[philo->id];
	philo->fork[1] = &table->forks[(philo->id + 1) % nb_philo];
	// philo->fork[0] = philo->id;
	// philo->fork[1] = (philo->id + 1) % nb_philo;
}

int	init_philo(t_table *table, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!philos)
		return (1); //ERROR HANDLING
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&(*philos)[i].meal_time_lock, NULL) != 0)
			return (1);
		(*philos)[i].id = i;
		(*philos)[i].eat_count = 0;
		(*philos)[i].table = table;
		assign_forks(&(*philos)[i], table, table->nb_philo);
		i++;
	}
	return (0);
}

void	init_table(t_table *table, int ac, char **av)
{
	int	i;

	i = 1;
	memset(table, 0, sizeof(t_table));
	table->nb_philo = philo_atoi(av[i++]);
	table->time_to_die = philo_atoi(av[i++]);
	table->time_to_eat = philo_atoi(av[i++]);
	table->time_to_sleep = philo_atoi(av[i++]);
	table->min_eat_count = -1;
	if (ac == 6)
		table->min_eat_count = philo_atoi(av[i++]);
	if (init_all_mutexes(table) != 0)
		return ; //ERROR HANDLING
	if (init_philo(table, &table->philos) != 0)
		return ; //ERROR HANDLING
}
