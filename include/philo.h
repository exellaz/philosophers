/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:06:42 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/11 15:35:32 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdio.h>

# define PHILO_MAX 200

typedef struct s_table t_table;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eat_count;
	int				fork[2];
	pthread_mutex_t	meal_time_lock;
	time_t			last_meal;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				nb_philo;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				min_eat_count;
	pthread_mutex_t	*forks;
	pthread_mutex_t	sim_end_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_table;

bool	ft_isdigit(char c);
bool	is_only_digits(char *str);
int		philo_atoi(char *str);
bool	is_valid_input(int ac, char **av);

void	init_table(t_table *table, int ac, char **av);

#endif
