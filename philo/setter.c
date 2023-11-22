/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:52:20 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/22 19:42:56 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_last_diner(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->diner_mutex[philo->index]);
	philo->last_diner = get_time();
	pthread_mutex_unlock(&philo->data->diner_mutex[philo->index]);
}

void	increment_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eaten_mutex[philo->index]);
	philo->eaten++;
	pthread_mutex_unlock(&philo->data->eaten_mutex[philo->index]);
}

static void	set_odd_or_even(t_philo *philo)
{
	if (philo->index % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		protected_print("has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
		protected_print("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		protected_print("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		protected_print("has taken a fork", philo);
	}
}

void	set_fork(t_philo *philo)
{
	set_odd_or_even(philo);
	protected_print("is eating", philo);
	set_last_diner(philo);
	sleep_until(get_time() + philo->data->time_to_eat);
	increment_eaten(philo);
	if (philo->index % 2 == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
