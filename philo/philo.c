/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:35:37 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/20 08:25:11 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	// printf("index: %i count philos %i\n", index, pcount);
	while ((get_time() - ((t_philo *)philo)->last_diner) <= ((t_philo *)philo)->data->time_to_die)
	{
		// printf("last diner from %i: %llu\n", index, ((t_philo *)philo)->last_diner);
		if (index == ((t_philo *)philo)->data->number_of_philosophers - 1)
		{
			pthread_mutex_lock(&((t_philo *)philo)->data->fork[index]);
			while (1)
				if (((t_philo *)philo)->data->fork_val[index] == 1)
					break ;
			printf("%llu %i has taken a fork\n", get_time(), index);
			((t_philo *)philo)->data->fork_val[index] = 0;
			pthread_mutex_lock(&((t_philo *)philo)->data->fork[0]);
			while (1)
				if (((t_philo *)philo)->data->fork_val[0] == 1)
					break ;
			printf("%llu %i has taken a fork\n", get_time(), index);
			((t_philo *)philo)->data->fork_val[0] = 0;
		}
		else
		{
			pthread_mutex_lock(&((t_philo *)philo)->data->fork[index]);
			while (1)
				if (((t_philo *)philo)->data->fork_val[index] == 1)
					break ;
			printf("%llu %i has taken a fork\n", get_time(), index);
			((t_philo *)philo)->data->fork_val[index] = 0;
			pthread_mutex_lock(&((t_philo *)philo)->data->fork[index + 1]);
			while (1)
				if (((t_philo *)philo)->data->fork_val[index + 1] == 1)
					break ;
			printf("%llu %i has taken a fork\n", get_time(), index);
			((t_philo *)philo)->data->fork_val[index + 1] = 0;
		}
		printf("%llu %i is eating\n", get_time(), index);
		((t_philo *)philo)->last_diner = get_time();
		usleep(((t_philo *)philo)->data->time_to_eat * 1000);
		if (index == ((t_philo *)philo)->data->number_of_philosophers - 1)
		{
			pthread_mutex_unlock(&((t_philo *)philo)->data->fork[index]);
			((t_philo *)philo)->data->fork_val[index] = 1;
			pthread_mutex_unlock(&((t_philo *)philo)->data->fork[0]);
			((t_philo *)philo)->data->fork_val[0] = 1;
		}
		else
		{
			pthread_mutex_unlock(&((t_philo *)philo)->data->fork[index]);
			((t_philo *)philo)->data->fork_val[index] = 1;
			pthread_mutex_unlock(&((t_philo *)philo)->data->fork[index + 1]);
			((t_philo *)philo)->data->fork_val[index + 1] = 1;
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

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	int		*ptr_result;

	if (argc < 5 || argc > 6)
		return (printf("wrong number of arguments\n"), 1);
	if (init_struct(&data, argc, argv))
		return (9);
	i = -1;
	while (++i < data.number_of_philosophers)
	{
		usleep(1);
		if (pthread_mutex_init(&data.fork[i], NULL) != 0)
			return (perror("create thread error"), i);
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
	free(data.fork);
	free(data.philo);
	return (0);
}