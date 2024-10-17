/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:53:51 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/17 14:18:58 by kkhai-ki         ###   ########.fr       */
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
# include <stdio.h>

# define PHILO_MAX 200

typedef struct s_table
{
	int	nb_philo;
	time_t	start_time;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		must_eat_count;
}	t_table;

int	philo_atoi(char *str);
bool	is_valid_input(int ac, char **av);

int	init_table(t_table *table, int ac, char **av);

#endif
