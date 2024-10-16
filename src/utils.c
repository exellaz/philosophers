/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:40:45 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/10/16 13:06:30 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *str, bool death_status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (sim_stopped(philo->table) == true && death_status == false)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		philo->id + 1, str);
	pthread_mutex_unlock(&philo->table->write_lock);
}
