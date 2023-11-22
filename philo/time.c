/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:21:29 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/22 09:17:21 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// return current time in milliseconds -> need to add start time
unsigned long long	get_time(t_data *data)
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
void	sleep_until(unsigned long long timestamp, t_data *data)
{
	int	i;

	i = 0;
	// printf("%llu sleeping until %llu\n", get_time(data), timestamp);
	while (get_time(data) < timestamp)
		usleep(100);
}
