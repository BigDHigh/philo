/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:35:37 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/23 08:21:00 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	while (get_run(data))
	{
		set_fork(philo);
		protected_print("is sleeping", philo);
		sleep_until(get_time() + data->time_to_sleep);
		protected_print("is thinking", philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	checker;

	if (check_input(argc, argv))
		return (1);
	if (one_philo(argv))
		return (0);
	if (init_struct(&data, argc, argv))
		return (printf("Initialization error\n"), 1);
	if (init_threads(&data, &checker))
		return (clean_data(&data), 1);
	if (clean(&data, &checker))
		return (1);
	return (0);
}
