/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:53:51 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/20 13:35:56 by kkhai-ki         ###   ########.fr       */
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

# define PHILO_MAX 200
# define SEM_FORKS "/philo_forks"
# define SEM_WRITE "/philo_write"
# define SEM_PHILO_FULL "/philo_full"
# define SEM_PHILO_DEAD "/philo_dead"
# define SEM_SIM_END "/philo_sim_end"
# define SEM_PHILO_EAT "/philo_eat"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int		id;
	sem_t	*sem_forks;
	sem_t	*sem_write;
	sem_t	*sem_philo_full;
	sem_t	*sem_philo_dead;
	sem_t	*sem_eat;
	char	*sem_eat_name;
	time_t	last_meal;
	int		eat_count;
	t_table	*table;
}	t_philo;

typedef struct s_table
{
	int		nb_philo;
	t_philo	*philos;
	t_philo	current_philo;
	time_t	start_time;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		must_eat_count;
	sem_t	*sem_forks;
	sem_t	*sem_write;
	sem_t	*sem_philo_full;
	sem_t	*sem_philo_dead;
	sem_t	*sem_sim_end;
	pid_t	*pids;
}	t_table;

int	philo_atoi(char *str);
bool	is_valid_input(int ac, char **av);

int	init_table(t_table *table, int ac, char **av);
void	cleanup_sem(t_table *table);

/*Utils*/
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_utoa(unsigned int nb, size_t len);
time_t	get_time_in_ms(void);
void	print_status(t_philo *philo, char *str);

/*Routines*/
void	philosopher(t_table *table);

#endif
