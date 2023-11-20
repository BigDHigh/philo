/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:21:29 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/20 18:22:43 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_time(void)
{
	struct timeval			time;
	unsigned long long		milliseconds;
	int						i;

	if (gettimeofday(&time, NULL))
		return (perror("Time error"), 0);
	milliseconds = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (milliseconds);
}

void	sleep_until(unsigned long long timestamp)
{
	int	i;

	i = 0;
	printf("%llu sleeping until %llu\n", get_time(), timestamp);
	while (get_time() < timestamp)
		usleep(1000);
}
