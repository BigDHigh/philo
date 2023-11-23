/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:12:22 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/23 08:21:45 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_eaten_meals(t_data *data)
{
	int	i;

	i = 0;
	if (data->max_eat == 0)
		return (0);
	while (i < data->number_of_philosophers)
	{
		if (!(get_eat(&data->philo[i]) >= data->max_eat))
			break ;
		i++;
	}
	if (i == data->number_of_philosophers)
		return (1);
	return (0);
}

// checking if any philosopher has died
// or if all philosophers have eaten max_eat times
void	*death_checker(t_data *data)
{
	int	i;
	int	dead;
	int	time_since_diner;

	dead = 0;
	while (!dead)
	{
		usleep(8000);
		i = -1;
		while (++i < data->number_of_philosophers)
		{
			time_since_diner = get_time() - get_last_diner(&data->philo[i]);
			if (time_since_diner > data->time_to_die || get_eaten_meals(data))
			{
				if (time_since_diner > data->time_to_die)
					protected_print("died", &data->philo[i]);
				dead = 1;
				break ;
			}
		}
	}
	return (set_run(data), NULL);
}

void	set_run(t_data *data)
{
	pthread_mutex_lock(&data->run_mutex);
	data->run = 0;
	pthread_mutex_unlock(&data->run_mutex);
}

int	get_run(t_data *data)
{
	int	run;

	pthread_mutex_lock(&data->run_mutex);
	run = data->run;
	pthread_mutex_unlock(&data->run_mutex);
	return (run);
}
