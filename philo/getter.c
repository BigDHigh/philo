/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:23:01 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/23 08:23:22 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// return time since last diner in milliseconds
unsigned long long	get_last_diner(t_philo *philo)
{
	unsigned long long	ret_val;

	pthread_mutex_lock(&philo->data->diner_mutex[philo->index]);
	ret_val = philo->last_diner;
	pthread_mutex_unlock(&philo->data->diner_mutex[philo->index]);
	return (ret_val);
}

// return count of how many times philo has eaten yes in milliseconds
int	get_eat(t_philo *philo)
{
	int	ret_val;

	pthread_mutex_lock(&philo->data->eaten_mutex[philo->index]);
	ret_val = philo->eaten;
	pthread_mutex_unlock(&philo->data->eaten_mutex[philo->index]);
	return (ret_val);
}
