/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 12:46:02 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/21 15:09:48 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sim_start_wait(time_t start_time)
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
	print_status(philo, "has taken a fork", false);
	philo_sleep(philo->table->time_to_die);
	print_status(philo, "died", true);
	exit(0);
}

static void	pick_up_fork(t_philo *philo)
{
	sem_wait(philo->sem_forks);
	sem_wait(philo->sem_eat);
	if (philo->forks_held <= 1)
		print_status(philo, "has taken a fork", false);
	philo->forks_held++;
	sem_post(philo->sem_eat);
}

static void	eat_sleep_routine(t_philo *philo)
{
	pick_up_fork(philo);
	pick_up_fork(philo);
	print_status(philo, "is eating", false);
	sem_wait(philo->sem_eat);
	philo->last_meal = get_time_in_ms();
	sem_post(philo->sem_eat);
	philo_sleep(philo->table->time_to_eat);
	print_status(philo, "is sleeping", false);
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
	sem_wait(philo->sem_eat);
	philo->forks_held -= 2;
	philo->eat_count++;
	sem_post(philo->sem_eat);
	philo_sleep(philo->table->time_to_sleep);
	print_status(philo, "is thinking", false);
}

void	*philosopher(t_table *table)
{
	t_philo	*philo;

	philo = &table->current_philo;
	if (table->nb_philo == 1)
		single_philo_routine(philo);
	if (table->must_eat_count == 0)
	{
		sem_post(philo->sem_philo_full);
		exit(0);
	}
	init_philo_ipc(table, philo);
	sem_wait(philo->sem_eat);
	philo->last_meal = table->start_time;
	sem_post(philo->sem_eat);
	sim_start_wait(table->start_time);
	if (philo->id % 2)
		usleep(5000);
	while (1)
	{
		if (philo->dead == true)
			exit(0) ;
		eat_sleep_routine(philo);
	}
	exit(0);
}
