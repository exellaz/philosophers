/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:53:51 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/25 14:44:56 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdatomic.h>

# define PHILO_MAX 200
# define EXIT_PHILO_FULL	12
# define EXIT_PHILO_DEAD	13
# define SEM_FORKS "/philo_forks"
# define SEM_WRITE "/philo_write"
# define SEM_PHILO_FULL "/philo_full"
# define SEM_PHILO_DEAD "/philo_dead"
# define SEM_SIM_END "/philo_sim_end"
# define SEM_PHILO_EAT "/philo_eat"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	int			eat_count;
	int			forks_held;
	bool		ate_enough;
	bool		dead;
	char		*sem_eat_name;
	sem_t		*sem_forks;
	sem_t		*sem_write;
	sem_t		*sem_philo_full;
	sem_t		*sem_philo_dead;
	sem_t		*sem_eat;
	time_t		last_meal;
	t_table		*table;
	pthread_t	local_monitor;
}	t_philo;

typedef struct s_table
{
	int				nb_philo;
	int				must_eat_count;
	int				philos_full;
	_Atomic bool	sim_end;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_philo_full;
	sem_t			*sem_philo_dead;
	sem_t			*sem_sim_end;
	pid_t			*pids;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	t_philo			*philos;
	t_philo			current_philo;
	pthread_t		global_death_monitor;
	pthread_t		global_eat_monitor;
}	t_table;

/*Parsing*/

int		philo_atoi(char *str);
bool	is_valid_input(int ac, char **av);

/*Init*/

int		init_table(t_table *table, int ac, char **av);

/*Utils*/

void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_utoa(unsigned int nb, size_t len);
size_t	ft_strlen(const char *s);
time_t	get_time_in_ms(void);

/*Philo Utils*/
void	print_status(t_philo *philo, char *str, bool death_report);
void	pick_up_fork(t_philo *philo);
void	philo_sleep(time_t sleep_time);
void	kill_philos(t_table *table);

/*Sim*/
int		start_sim(t_table *table);
int		stop_sim(t_table *table);
bool	sim_ended(t_table *table);
void	sim_start_wait(time_t start_time);

/*Routines*/

void	*philosopher(t_table *table);
void	*local_monitor(void *data);
void	*global_death_monitor(void *data);
void	*global_eat_monitor(void *data);

/*IPC*/

void	init_philo_ipc(t_table *table, t_philo *philo);

/*Cleanup*/
void	cleanup_sem(t_table *table);
void	unlink_global_sem(void);

#endif
