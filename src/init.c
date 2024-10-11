/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:06:01 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/11 14:50:33 by kkhai-ki         ###   ########.fr       */
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

bool	init_all_mutexes(t_table *table)
{
	table->forks = init_forks(table);
	if (!table->forks)
		return (false);
	if (pthread_mutex_init(&table->sim_end_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (false);
	return (true);
}

void	init_table(t_table *table, int ac, char **av)
{
	int	i;

	i = 1;
	memset(&table, 0, sizeof(t_table));
	table->nb_philo = philo_atoi(av[i++]);
	table->time_to_die = philo_atoi(av[i++]);
	table->time_to_eat = philo_atoi(av[i++]);
	table->time_to_sleep = philo_atoi(av[i++]);
	table->min_eat_count = 0;
	if (ac == 6)
		table->min_eat_count = philo_atoi(av[i++]);
	if (init_all_mutex(table != 0))
		return ;

}

