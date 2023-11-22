/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:13:30 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/22 20:21:32 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// free malloced data
void	clean_data(t_data *data)
{
	free(data->fork);
	free(data->philo);
	free(data->fork_val);
	free(data->diner_mutex);
	free(data->eaten_mutex);
}

// join threads and tidy up (destroy mutexes free data)
int	clean(t_data *data, pthread_t *checker)
{
	int	i;

	if (pthread_join(*checker, NULL))
		return (perror("join thread error"), 1);
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (perror("join thread error"), 1);
	}
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->fork[i]);
	clean_data(data);
	return (0);
}
