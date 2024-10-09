/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:06:42 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/09 19:53:48 by kkhai-ki         ###   ########.fr       */
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

typedef struct s_table
{
	int		nb_philo;
	time_t	start_time;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		min_eat_count;
}	t_table;

#endif
