/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:27:59 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/22 21:28:28 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*just_die(t_data *data)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("0 1 has taken a fork\n");
	usleep(data->time_to_die * 1000);
	printf("%i 1 died\n", data->time_to_die);
	pthread_mutex_unlock(&data->print_mutex);
	return (NULL);
}

int	one_philo(char **argv)
{
	pthread_t		thread;
	t_data			data;
	pthread_mutex_t	mutex;

	if (ft_atoi(argv[1]) != 1)
		return (0);
	pthread_mutex_init(&mutex, NULL);
	data.time_to_die = ft_atoi(argv[2]);
	data.print_mutex = mutex;
	if (pthread_create(&thread, NULL, (t_funct) & just_die, &data))
		return (perror("thread error"), 1);
	if (pthread_join(thread, NULL))
		return (perror("join thread error"), 1);
	pthread_mutex_destroy(&mutex);
	return (1);
}
