/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:20:16 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/20 09:50:09 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_struct(t_data *data, int argc, char **argv)
{
	int	i;

	i = -1;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_oftimeseach_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_oftimeseach_philosopher_must_eat = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	data->fork_val = malloc(sizeof(int) * data->number_of_philosophers);
	if (!data->fork || !data->philo)
		return (perror("malloc error"), 1);
	while (++i < data->number_of_philosophers)
	{
		data->fork_val[i] = 1;
		data->philo[i].index = i;
		data->philo[i].data = data;
		data->philo[i].last_diner = get_time();
	}
	return (0);
}
