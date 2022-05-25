/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:06:04 by ybendavi          #+#    #+#             */
/*   Updated: 2022/05/23 20:25:39 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	mutex_destroyer_p2(pthread_mutex_t *mutex, short int i)
{
	while (i > -1)
	{
		if (&mutex[i])
			pthread_mutex_destroy(&mutex[i]);
		i--;
	}
}

void	mutex_destroyer(t_env *env)
{
	short int	i;

	i = env->data->number_of_philosophers - 1;
	mutex_destroyer_p2(env->data->fork, i);
	pthread_mutex_destroy(&env->data->print);
	if (env->data->fork)
		free(env->data->fork);
}

void	print_death(short int philoid, size_t time, t_env *env)
{
	printf("%zu %d %s\n", time - env->data->zero_time, philoid, "died");
}

void	freer(t_env *env)
{
	short int	k;
	short int	i;

	k = env->data->number_of_philosophers - 1;
	i = env->data->all_death;
	while (k > -1)
	{
		if (env->philo[k].thread)
			pthread_join(env->philo[k].thread, NULL);
		k--;
	}
	k = i;
	i = env->data->number_of_philosophers - 1;
	if (k)
	{
		while (i != k - 1)
			i--;
		print_death(k, timestamp(), env);
	}
	mutex_destroyer(env);
	if (env->philo)
		free(env->philo);
}
