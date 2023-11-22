/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:24:49 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/22 21:08:22 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv)
{
	int	i;
	int	argc_copy;

	argc_copy = argc;
	if (argc < 5 || argc > 6)
		return (printf("Error: wrong number of arguments\n"), 1);
	while (--argc > 0)
	{
		i = -1;
		while (argv[argc][++i])
		{
			if (!ft_isdigit(argv[argc][i]))
				return (printf("Error: non numeric argument\n"), 1);
		}
		if (i == 0)
			return (printf("Error: empty argument\n"), 1);
	}
	if (ft_atoi(argv[1]) < 1)
		return (printf("Error: no philosopher\n"), 1);
	if (argc_copy == 6 && ft_atoi(argv[5]) == 0)
		return (printf("Error: invalid \
[number_of_times_each_philosopher_must_eat]\n"), 1);
	return (0);
}
