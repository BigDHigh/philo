/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:12:22 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/20 11:36:13 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_checker(void *data)
{
	int		i;
	int		dead;
	t_data	*data_ptr;

	dead = 0;
	data_ptr = (t_data *)data;
	while (!dead)
	{
		i = -1;
		while (++i < data_ptr->number_of_philosophers)
		{
			if (data_ptr->philo[i].dead == 1)
			{
				dead = 1;
				break ;
			}
		}
	}
}
