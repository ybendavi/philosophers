/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:30:22 by ybendavi          #+#    #+#             */
/*   Updated: 2022/05/24 14:23:29 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

short int	init_mutex_p2(pthread_mutex_t *mutex, int i)
{
	while (i > -1)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i--;
	}
	return (0);
}

short int	init_mutex(t_env *env)
{
	short int	i;

	i = env->data->number_of_philosophers;
	env->data->fork = malloc(sizeof(pthread_mutex_t) * i);
	if (!(env->data->fork))
		return (1);
	i--;
	init_mutex_p2(env->data->fork, i);
	pthread_mutex_init(&env->data->print, NULL);
	pthread_mutex_init(&env->data->a_eat, NULL);
	pthread_mutex_init(&env->data->a_death, NULL);
	pthread_mutex_init(&env->data->l_meal, NULL);
	return (0);
}

short int	init_data(char **av, t_env *env)
{
	if (ft_atoi(av[0]) > 10000 || ft_atoi(av[0]) < 0
		|| ft_atoi(av[1]) < 0 || ft_atoi(av[1]) > 1000000
		|| ft_atoi(av[2]) < 0 || ft_atoi(av[2]) > 1000000
		|| ft_atoi(av[3]) < 0 || ft_atoi(av[3]) > 1000000
		|| (av[4] && ft_atoi(av[4]) > 1000000))
	{
		return (1);
	}
	env->data->number_of_philosophers = ft_atoi(av[0]);
	env->data->time_to_die = ft_atoi(av[1]);
	env->data->time_to_eat = ft_atoi(av[2]);
	env->data->time_to_sleep = ft_atoi(av[3]);
	if (av[4])
		env->data->number_of_times_each_philosopher_must_eat = ft_atoi(av[4]);
	else
		env->data->number_of_times_each_philosopher_must_eat = -1;
	env->data->all_death = 0;
	env->data->all_eat = 0;
	env->data->death = 1;
	return (0);
}

short int	init_philo(t_env *env)
{
	short int	k;

	k = env->data->number_of_philosophers;
	env->philo = malloc(sizeof(t_philo) * k);
	if (!env->philo)
		return (1);
	k--;
	while (k > -1)
	{
		env->philo[k].id = k + 1;
		env->philo[k].left_fork_id = k;
		if (k == 0)
			env->philo[k].right_fork_id = env->data->number_of_philosophers - 1;
		else
			env->philo[k].right_fork_id = k - 1;
		env->philo[k].data = env->data;
		env->philo[k].eat_count = 0;
		env->philo[k].die = 1;
		env->philo[k].thread = 0;
		k--;
	}
	return (0);
}

short int	init_all(char **av, t_env *env)
{
	env->philo = NULL;
	env->data->fork = NULL;
	if (init_data(av, env) == 1)
		return (1);
	if (init_mutex(env) == 1)
		return (1);
	if (init_philo(env) == 1)
		return (1);
	env->data->zero_time = timestamp();
	return (0);
}
