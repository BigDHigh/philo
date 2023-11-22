/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:07:18 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/22 18:58:43 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	while (*s)
	{
		ft_putchar(*s++);
	}
}

void	ft_putnbr(unsigned long long n)
{
	{
		if (n > 9)
		{
			ft_putnbr(n / 10);
		}
		if (n < 10)
			ft_putchar(n + '0');
		else
			ft_putchar((n % 10) + '0');
		return ;
	}
}

// void	protected_print(char *str, t_philo *philo)
// {

// 	pthread_mutex_lock(&philo->data->print_mutex);
// 	if (get_run(philo->data))
// 	{
// 		ft_putnbr(get_time(philo->data));
// 		ft_putchar(' ');
// 		ft_putnbr((unsigned long long)philo->index + 1);
// 		ft_putchar(' ');
// 		ft_putstr(str);
// 		ft_putchar('\n');
// 	}
// 	pthread_mutex_unlock(&philo->data->print_mutex);
// }

void	protected_print(char *str, t_philo *philo)
{
	if (get_run(philo->data))
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		ft_putnbr(get_time_stamp(philo->data));
		ft_putchar(' ');
		ft_putnbr((unsigned long long)philo->index + 1);
		ft_putchar(' ');
		ft_putstr(str);
		ft_putchar('\n');
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
}
