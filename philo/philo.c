/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:35:37 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/16 21:23:05 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_time(void)
{
	struct timeval			time;
	unsigned long long		milliseconds;

	if (gettimeofday(&time, NULL))
		return (perror("Time error"), 0);
	milliseconds = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (milliseconds);
}

int	init_struct(t_data *data)
{
	int	i;

	i = -1;
	data->number_of_philosophers = 5;
	data->time_to_die = 310;
	data->time_to_eat = 200;
	data->time_to_sleep = 100;
	data->number_oftimeseach_philosopher_must_eat = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->fork || !data->philo)
		return (perror("malloc error"), 1);
	while (++i < data->number_of_philosophers)
	{
		data->philo[i].index = i;
		data->philo[i].data = data;
		data->philo[i].last_diner = get_time();
	}
	return (0);
}

void	*routine(void *philo)
{
	int	i;
	int	index;
	int	*iptr;
	int	pcount;
	int	time;

	time = 0;
	i = 0;
	index = ((t_philo *)philo)->index;
	pcount = ((t_philo *)philo)->data->number_of_philosophers;
	printf("index: %i count philos %i\n", index, pcount);
	while ((get_time() - ((t_philo *)philo)->last_diner) <= ((t_philo *)philo)->data->time_to_die)
	{
		printf("time since last diner: %llu\n", (get_time() - ((t_philo *)philo)->last_diner));
		if (index == ((t_philo *)philo)->data->number_of_philosophers - 1)
		{
			pthread_mutex_lock(&((t_philo *)philo)->data->fork[index]);
			printf("%llu %i has taken a fork\n", get_time(), index);
			pthread_mutex_lock(&((t_philo *)philo)->data->fork[0]);
			printf("%llu %i has taken a fork\n", get_time(), index);
		}
		else
		{
			pthread_mutex_lock(&((t_philo *)philo)->data->fork[index]);
			printf("%llu %i has taken a fork\n", get_time(), index);
			pthread_mutex_lock(&((t_philo *)philo)->data->fork[index + 1]);
			printf("%llu %i has taken a fork\n", get_time(), index);
		}
		printf("%llu %i is eating\n", get_time(), index);
		((t_philo *)philo)->last_diner = get_time();
		printf("last diner: %llu\n", ((t_philo *)philo)->last_diner);
		usleep(((t_philo *)philo)->data->time_to_eat * 1000);
		if (index == ((t_philo *)philo)->data->number_of_philosophers - 1)
		{
			pthread_mutex_unlock(&((t_philo *)philo)->data->fork[index]);
			pthread_mutex_unlock(&((t_philo *)philo)->data->fork[0]);
		}
		else
		{
			pthread_mutex_unlock(&((t_philo *)philo)->data->fork[index]);
			pthread_mutex_unlock(&((t_philo *)philo)->data->fork[index + 1]);
		}
		printf("%llu %i is sleeping\n", get_time(), index);
		usleep(((t_philo *)philo)->data->time_to_sleep * 1000);
		printf("%llu %i is thinking\n", get_time(), index);
	}
	printf("%llu %i died\n", get_time(), index);
	iptr = malloc(sizeof(int));
	*iptr = index;
	return ((void *) iptr);
}

int	main(void)
{
	t_data	data;
	int		i;
	int		*ptr_result;

	if (init_struct(&data))
		return (9);
	i = -1;
	while (++i < data.number_of_philosophers)
	{
		pthread_mutex_init(&data.fork[i], NULL);
		if (pthread_create(&data.philo[i].thread, NULL, &routine, &data.philo[i]) != 0)
			return (perror("create thread error"), i);
	}
	i = -1;
	while (++i < data.number_of_philosophers)
	{
		if (pthread_join(data.philo[i].thread, (void **) &ptr_result))
			return (perror("join thread error"), i);
	}
	i = -1;
	while (++i < data.number_of_philosophers)
		pthread_mutex_destroy(&data.fork[i]);
	printf("last result: %i\n", *ptr_result);
	free(data.fork);
	free(data.philo);
	return (0);
}
