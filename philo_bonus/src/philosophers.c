/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 12:46:02 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/23 18:39:55 by kkhai-ki         ###   ########.fr       */
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

void	think_routine(t_philo *philo)
{
	time_t	think_time;

	sem_wait(philo->sem_eat);
	think_time = (philo->table->time_to_die - (get_time_in_ms() - philo->last_meal) - philo->table->time_to_eat) / 2;
	sem_post(philo->sem_eat);
	if (think_time <= 0)
		think_time = 1;
	if (think_time > 600)
		think_time = 200;
	print_status(philo, "is thinking", false);
	philo_sleep(think_time);
}

static void	single_philo_routine(t_philo *philo)
{
	// philo->sem_philo_full = sem_open(SEM_PHILO_FULL, O_CREAT, S_IRUSR | S_IWUSR, philo->table->nb_philo);
	// if (philo->sem_philo_full == SEM_FAILED)
	// 	exit(1);
	init_philo_ipc(philo->table, philo);
	sem_wait(philo->sem_philo_full);
	sim_start_wait(philo->table->start_time);
	if (philo->table->must_eat_count == 0)
	{
		sem_post(philo->sem_philo_full);
		exit(SINGLE_PHILO_EXIT);
	}
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		philo->id + 1, "has taken a fork");
	philo_sleep(philo->table->time_to_die);
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		philo->id + 1, "died");
	exit(SINGLE_PHILO_EXIT);
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

static void	eat_sleep_think(t_philo *philo)
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
	if (philo->table->nb_philo % 2 != 0)
		think_routine(philo);
	else
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
		eat_sleep_think(philo);
	exit(0);
}
