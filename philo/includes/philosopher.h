/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:49:00 by ybendavi          #+#    #+#             */
/*   Updated: 2022/05/24 14:49:03 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data {
	unsigned short int			number_of_philosophers;
	unsigned int				time_to_die;
	unsigned int				time_to_eat;
	unsigned int				time_to_sleep;
	unsigned short int			all_death;
	unsigned short int			all_eat;
	char						death;
	size_t						zero_time;
	size_t						death_time;
	pthread_mutex_t				a_eat;
	pthread_mutex_t				print;
	pthread_mutex_t				a_death;
	pthread_mutex_t				l_meal;
	int							number_of_times_each_philosopher_must_eat;
	pthread_mutex_t				*fork;
}								t_data;

typedef struct s_philosopher {
	unsigned short int			id;
	unsigned short int			left_fork_id;
	unsigned short int			right_fork_id;
	int							eat_count;
	int							die;
	unsigned short int			round_table;
	size_t						last_meal;
	pthread_t					thread;
	t_data						*data;
}				t_philo;

typedef struct s_env {
	t_data			*data;
	t_philo			*philo;
}			t_env;

int					ft_atoi(char *str);
short int			check_arg(char **argv);
short int			check(t_philo *philo);
short int			eat(t_philo *philo);
short int			death_checker(t_philo *philo);
short int			philo(char **argv);
void				print_message(t_philo *philo, const char *str);
void				sleeping(t_philo *philo);
void				eval_rt(t_philo *philo);
short int			eat_condition(t_philo *philo);
void				sleep_step(t_philo *philo, unsigned int data);
void				die(t_philo *philo, char d);
size_t				timestamp(void);
short int			init_all(char **av, t_env *env);
void				freer(t_env *env);

#endif
