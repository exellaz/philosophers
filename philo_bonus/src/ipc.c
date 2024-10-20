/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:53:31 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/20 15:39:40 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	open_philo_global_sem(t_philo *philo)
{
	philo->sem_forks = sem_open(SEM_FORKS, O_CREAT,
			S_IRUSR | S_IWUSR, philo->table->nb_philo);
	if (philo->sem_forks == SEM_FAILED)
		return (1);
	philo->sem_write = sem_open(SEM_WRITE, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (philo->sem_write == SEM_FAILED)
		return (1);
	philo->sem_philo_full = sem_open(SEM_PHILO_FULL, O_CREAT,
			S_IRUSR | S_IWUSR, philo->table->nb_philo);
	if (philo->sem_philo_full == SEM_FAILED)
		return (1);
	philo->sem_philo_dead = sem_open(SEM_PHILO_DEAD, O_CREAT,
			S_IRUSR | S_IWUSR, philo->table->nb_philo);
	if (philo->sem_philo_dead == SEM_FAILED)
		return (1);
	return (0);
}

static int	open_philo_eat_sem(t_philo *philo)
{
	philo->sem_eat = sem_open(philo->sem_eat_name, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (philo->sem_eat == SEM_FAILED)
		return (1);
	sem_unlink(philo->sem_eat_name);
	return (0);
}

void	init_philo_ipc(t_table *table, t_philo *philo)
{
	if (table->nb_philo == 1)
		return ;
	sem_unlink(philo->sem_eat_name);
	if (open_philo_global_sem(philo) != 0)
		exit(1);
	if (open_philo_eat_sem(philo) != 0)
		exit(1);
	return ;
}
