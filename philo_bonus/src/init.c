/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:14:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/25 14:44:42 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	open_table_global_sem(t_table *table)
{
	unlink_global_sem();
	table->sem_forks = sem_open(SEM_FORKS, O_CREAT,
			S_IRUSR | S_IWUSR, table->nb_philo);
	if (table->sem_forks == SEM_FAILED)
		return (1);
	table->sem_write = sem_open(SEM_WRITE, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (table->sem_write == SEM_FAILED)
		return (1);
	table->sem_philo_full = sem_open(SEM_PHILO_FULL, O_CREAT,
			S_IRUSR | S_IWUSR, table->nb_philo);
	if (table->sem_philo_full == SEM_FAILED)
		return (1);
	table->sem_philo_dead = sem_open(SEM_PHILO_DEAD, O_CREAT,
			S_IRUSR | S_IWUSR, table->nb_philo);
	if (table->sem_philo_dead == SEM_FAILED)
		return (1);
	table->sem_sim_end = sem_open(SEM_SIM_END, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (table->sem_sim_end == SEM_FAILED)
		return (1);
	return (0);
}

static int	set_sem_eat_name(t_philo *philo, char *str, unsigned int id)
{
	unsigned int	i;
	unsigned int	digit_count;
	char			*sem_name;
	char			*id_str;

	digit_count = 0;
	i = id;
	while (i)
	{
		digit_count++;
		i /= 10;
	}
	i = ft_strlen(str) + digit_count;
	sem_name = malloc(sizeof(char) * 1);
	if (sem_name == NULL)
		return (1);
	sem_name[0] = '\0';
	sem_name = ft_strjoin(sem_name, str);
	id_str = ft_utoa(id, digit_count);
	sem_name = ft_strjoin(sem_name, id_str);
	free(id_str);
	philo->sem_eat_name = sem_name;
	return (0);
}

static int	init_philosophers(t_table *table, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * (table->nb_philo));
	if (!*philos)
		return (printf("Could not allocate memory\n"), 2);
	memset(*philos, 0, (sizeof(t_philo) * table->nb_philo));
	i = 0;
	while (i < table->nb_philo)
	{
		(*philos)[i].id = i;
		(*philos)[i].table = table;
		(*philos)[i].last_meal = table->start_time;
		if (set_sem_eat_name(&(*philos)[i], SEM_PHILO_EAT, i) != 0)
			return (printf("Could not open philosopher sem\n"), 1);
		i++;
	}
	return (0);
}

int	init_table(t_table *table, int ac, char **av)
{
	memset(table, 0, sizeof(t_table));
	table->sim_end = false;
	table->nb_philo = philo_atoi(av[1]);
	table->time_to_die = philo_atoi(av[2]);
	table->time_to_eat = philo_atoi(av[3]);
	table->time_to_sleep = philo_atoi(av[4]);
	table->must_eat_count = -1;
	if (ac == 6)
		table->must_eat_count = philo_atoi(av[5]);
	if (open_table_global_sem(table) != 0)
		return (printf("Could not open global sem\n"), 1);
	if (init_philosophers(table, &table->philos) != 0)
		return (1);
	table->pids = malloc(sizeof(pid_t) * table->nb_philo);
	if (!table->pids)
		return (printf("Could not allocate memory\n"), free(table->philos), 2);
	return (0);
}
