/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:21:29 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/22 18:43:05 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// return current time in milliseconds
unsigned long long	get_time(void)
{
	struct timeval			time;
	unsigned long long		milliseconds;

	if (gettimeofday(&time, NULL))
		return (perror("Time error"), 0);
	milliseconds = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (milliseconds);
}

// return current time in milliseconds after start
unsigned long long	get_time_stamp(t_data *data)
{
	struct timeval			time;
	unsigned long long		milliseconds;

	if (gettimeofday(&time, NULL))
		return (perror("Time error"), 0);
	milliseconds = time.tv_usec / 1000 + time.tv_sec * 1000;
	milliseconds -= data->start;
	return (milliseconds);
}

// sleep until timestamp
// void	sleep_until(unsigned long long timestamp, t_data *data)
void	sleep_until(unsigned long long timestamp)
{
	int	i;

	i = 0;
	while (get_time() < timestamp)
		usleep(100);
}
