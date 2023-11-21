/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:12:22 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/21 19:46:52 by dnebatz          ###   ########.fr       */
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
		// printf("%i has eaten %i times\n\n\n", i, data->philo[i].eaten);
	}
	if (ate_enough == data->number_of_philosophers)
	{
		// printf("All philosophers have eaten %i times\n\n\n", data->max_eat);
		return (1);
	}
	return (0);
}

// checking if any philosopher has died
// or if all philosophers have eaten max_eat times
void	*death_checker(void *void_data)
{
	int		i;
	int		dead;
	t_data	*data;

	dead = 0;
	data = (t_data *)void_data;
	while (!dead)
	{
		usleep(10000);
		i = -1;
		while (++i < data->number_of_philosophers)
		{
			// if ((get_time(data) - data->philo[i].last_diner >= data->time_to_die) || get_eaten_meals(data))
			if (get_time(data) - get_last_diner(&data->philo[i]) >= data->time_to_die)
			{
				
				protected_print("died", &data->philo[i]);
				// printf("%llu %i died because: %llu - %llu >= %d\n", get_time(data), i, get_time(data), data->philo[i].last_diner, data->time_to_die);
				dead = 1;
				break ;
			}
			if (get_eaten_meals(data))
			{
				printf("you ate enough\n");
				dead = 1;
				break ;
			}
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
