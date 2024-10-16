/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:06:01 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/16 13:48:09 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!forks)
		return (printf("Could not allocate memory\n"), NULL);
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (printf("Could not create mutex\n"), NULL);
		i++;
	}
	return (forks);
}

static int	init_philo(t_table *table, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!philos)
		return (printf("Could not allocate memory\n"), 1);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&(*philos)[i].meal_time_lock, NULL) != 0)
			return (printf("Could not create mutex\n"), 1);
		(*philos)[i].id = i;
		(*philos)[i].eat_count = 0;
		(*philos)[i].table = table;
		(*philos)[i].fork[0] = &table->forks[i];
		(*philos)[i].fork[1] = &table->forks[(i + 1) % table->nb_philo];
		i++;
	}
	return (0);
}

static int	init_all_mutexes(t_table *table)
{
	table->forks = init_forks(table);
	if (!table->forks)
		return (1);
	if (pthread_mutex_init(&table->sim_end_lock, NULL) != 0)
		return (printf("Could not create mutex\n"), 1);
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (printf("Could not create mutex\n"), 1);
	return (0);
}

int	init_table(t_table *table, int ac, char **av)
{
	int	i;

	i = 1;
	memset(table, 0, sizeof(t_table));
	table->nb_philo = philo_atoi(av[i++]);
	table->time_to_die = philo_atoi(av[i++]);
	table->time_to_eat = philo_atoi(av[i++]);
	table->time_to_sleep = philo_atoi(av[i++]);
	table->must_eat_count = -1;
	if (ac == 6)
		table->must_eat_count = philo_atoi(av[i++]);
	if (init_all_mutexes(table) != 0)
		return (1);
	if (init_philo(table, &table->philos) != 0)
		return (1);
	return (0);
}
