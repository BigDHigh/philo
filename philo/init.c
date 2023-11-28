/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:20:16 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/28 18:47:20 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// initialize philosophers struct
static int	init_philos(t_data *data)
{
	int	i;
	int	left_fork;
	int	right_fork;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (i == 0)
			right_fork = data->number_of_philosophers - 1;
		else
			right_fork = i - 1;
		left_fork = i;
		data->philo[i].left_fork = &data->fork[left_fork];
		data->philo[i].right_fork = &data->fork[right_fork];
		data->fork_val[i] = 1;
		data->philo[i].index = i;
		data->philo[i].data = data;
		data->philo[i].eaten = 0;
		data->philo[i].last_diner = get_time();
	}
	return (0);
}

// initialize data struct
int	init_struct(t_data *data, int argc, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start = 0;
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	else
		data->max_eat = 0;
	data->run = 1;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	data->fork_val = malloc(sizeof(int) * data->number_of_philosophers);
	data->diner_mutex = malloc
		(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	data->eaten_mutex = malloc
		(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->fork || !data->philo || !data->fork_val || !data->diner_mutex
		|| !data->eaten_mutex)
		return (clean_data(data), perror("malloc error"), 1);
	if (init_philos(data))
		return (clean_data(data), 1);
	data->start = get_time();
	return (0);
}

// create threads for philosophers and death checker
int	init_threads(t_data *data, pthread_t *checker)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->run_mutex, NULL) != 0)
		return (perror("create mutex error"), 1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (perror("create mutex error"), 1);
	while (++i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (perror("create mutex error"), 1);
		if (pthread_mutex_init(&data->eaten_mutex[i], NULL) != 0)
			return (perror("create mutex error"), 1);
		if (pthread_mutex_init(&data->diner_mutex[i], NULL) != 0)
			return (perror("create mutex error"), 1);
		if (pthread_create(&data->philo[i].thread, NULL,
				(t_funct) & routine, &data->philo[i]) != 0)
			return (perror("create thread error"), 1);
		usleep(10);
	}
	if (pthread_create(checker, NULL, (t_funct) & death_checker, data) != 0)
		return (perror("create thread error"), 1);
	return (0);
}
