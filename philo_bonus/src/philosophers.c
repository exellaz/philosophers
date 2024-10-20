/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 12:46:02 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/20 13:33:56 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sim_start_wait(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue ;
}

static void	philo_sleep(time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
		usleep(100);
}

static void	single_philo_routine(t_philo *philo)
{
	philo->sem_philo_full = sem_open(SEM_PHILO_FULL, O_CREAT, S_IRUSR | S_IWUSR, philo->table->nb_philo);
	if (philo->sem_philo_full == SEM_FAILED)
		exit(1);
	sem_wait(philo->sem_philo_full);
	sim_start_wait(philo->table->start_time);
	if (philo->table->must_eat_count == 0)
	{
		sem_post(philo->sem_philo_full);
		exit(1);
	}
	print_status(philo, "has taken a fork");
	philo_sleep(philo->table->time_to_die);
	print_status(philo, "died");
	exit(1);
}

void	philosopher(t_table *table)
{
	t_philo	*philo;

	philo = &table->current_philo;
	if (philo->table->nb_philo == 1)
		single_philo_routine(philo);
}
