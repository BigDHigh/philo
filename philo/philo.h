/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:31:28 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/22 20:26:13 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;
typedef void *			(*t_funct)(void *);

typedef struct s_philo
{
	pthread_t			thread;
	int					index;
	t_data				*data;
	unsigned long long	last_diner;
	int					should_eat;
	int					dead;
	int					eaten;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t		*fork;
	pthread_mutex_t		run_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		*eaten_mutex;
	pthread_mutex_t		*diner_mutex;
	int					*fork_val;
	t_philo				*philo;
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat;
	int					run;
	unsigned long long	start;
}	t_data;

int						init_struct(t_data *data, int argc, char **argv);
unsigned long long		get_time(void);
unsigned long long		get_time_stamp(t_data *data);
int						ft_atoi(const char *str);
void					*death_checker(t_data *data);
void					sleep_until(unsigned long long timestamp);
void					*routine(t_philo *philo);
int						init_threads(t_data *data, pthread_t *checker);
int						clean(t_data *data, pthread_t *checker);
void					clean_data(t_data *data);
void					set_run(t_data *data);
int						get_run(t_data *data);
void					protected_print(char *str, t_philo *philo);
void					set_fork(t_philo *philo);
unsigned long long		get_last_diner(t_philo *philo);
int						get_eat(t_philo *philo);
int						check_input(int argc, char **argv);
int						ft_isdigit(int c);

#endif