/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:12:22 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/22 09:34:55 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// return 1 if all philosophers have eaten max_eat times
int	get_eaten_meals(t_data *data)
{
	int	i;
	int	ate_enough;

	i = -1;
	ate_enough = 0;
	if (data->max_eat == 0)
		return (0);
	while (++i < data->number_of_philosophers)
	{
		if (get_eat(&data->philo[i]) >= data->max_eat)
			ate_enough++;
	}
	if (ate_enough == data->number_of_philosophers)
	{
		return (1);
	}
	return (0);
}

// checking if any philosopher has died
// or if all philosophers have eaten max_eat times
void	*death_checker(void *void_data)
{
	int		i;
	t_data	*data;

	data = (t_data *)void_data;
	while (1)
	{
		usleep(10000);
		i = -1;
		while (++i < data->number_of_philosophers)
		{
			if (get_time(data) - get_last_diner
				(&data->philo[i]) >= (unsigned long long)data->time_to_die)
			{
				protected_print("died", &data->philo[i]);
				break ;
			}
			if (get_eaten_meals(data))
				break ;
		}
	}
	set_run(data);
	return (NULL);
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
