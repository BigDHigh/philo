/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:35:37 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/21 16:04:25 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *void_philo)
{
	int		index;
	int		pcount;
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)((t_philo *)void_philo)->data;
	philo = (t_philo *)void_philo;
	index = philo->index;
	pcount = data->number_of_philosophers;
	while (get_run(data))
	{
		set_fork(philo);
		protected_print("is sleeping", philo);
		sleep_until(get_time(data) + data->time_to_sleep, data);
		protected_print("is thinking", philo);
	}
	printf("%llu %i thread ending\n", get_time(data), index);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			*ptr_result;
	pthread_t	checker;

	if (argc < 5 || argc > 6)
		return (printf("Error: wrong number of arguments\n"), 1);
	// printf("timestamp: %llu\n", get_time(&data));
	// sleep_until(get_time(&data) + 1000, &data);
	if (init_struct(&data, argc, argv))
		return (printf("Initialization error\n"), 1);
	// printf("timestamp: %llu\n", get_time(&data));
	if (init_threads(&data, &checker))
		return (clean_data(&data), 1);
	if (clean(&data, &checker))
		return (1);
	return (0);
}
