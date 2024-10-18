/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:14:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/18 13:42:02 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

static void	unlink_global_sem(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_PHILO_FULL);
	sem_unlink(SEM_PHILO_DEAD);
	sem_unlink(SEM_SIM_END);
}

//Check semaphores using ls /dev/shm
void	cleanup_sem(t_table *table)
{
	sem_close(table->sem_forks);
	sem_close(table->sem_write);
	sem_close(table->sem_philo_full);
	sem_close(table->sem_philo_dead);
	sem_close(table->sem_sim_end);
	unlink_global_sem();
}

static int	init_global_sem(t_table *table)
{
	unlink_global_sem();
	table->sem_forks = sem_open(SEM_FORKS, O_CREAT, S_IRUSR | S_IWUSR, table->nb_philo);
	if (table->sem_forks == SEM_FAILED)
		return (1);
	table->sem_write = sem_open(SEM_WRITE, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (table->sem_write == SEM_FAILED)
		return (1);
	table->sem_philo_full = sem_open(SEM_PHILO_FULL, O_CREAT, S_IRUSR | S_IWUSR, table->nb_philo);
	if (table->sem_philo_full == SEM_FAILED)
		return (1);
	table->sem_philo_dead = sem_open(SEM_PHILO_DEAD, O_CREAT, S_IRUSR | S_IWUSR, table->nb_philo);
	if (table->sem_philo_dead == SEM_FAILED)
		return (1);
	table->sem_sim_end = sem_open(SEM_SIM_END, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (table->sem_sim_end == SEM_FAILED)
		return (1);
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
	if (init_global_sem(table) != 0)
		return (1);
	return (0);
}
