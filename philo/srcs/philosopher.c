/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:15:10 by ybendavi          #+#    #+#             */
/*   Updated: 2022/05/24 15:03:21 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_message(t_philo *philo, const char *str)
{
	char	death;

	pthread_mutex_lock(&philo->data->a_death);
	death = philo->data->death;
	pthread_mutex_unlock(&philo->data->a_death);
	if (death)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%zu %d %s\n", timestamp() - philo->data->zero_time,
			philo->id, str);
		pthread_mutex_unlock(&philo->data->print);
	}
}

void	eval_rt(t_philo *philo)
{
	if (philo->round_table == philo->data->number_of_philosophers)
		philo->round_table = 1;
	else
		philo->round_table++;
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->round_table = philo->data->number_of_philosophers;
	if (philo->id % 2 != 0)
	{
		sleep_step(philo, 2);
		eval_rt(philo);
	}
	sleep_step(philo, 0);
	while (philo->die)
	{
		if (philo->data->number_of_philosophers % 2 != 0)
		{
			if (eat_condition(philo) == 0)
			{
				eval_rt(philo);
				sleep_step(philo, philo->data->time_to_eat);
			}
		}
		eat(philo);
		sleeping(philo);
		print_message(philo, "is thinking");
	}
	return (philo);
}

short int	set_last_meal(t_philo *philo, short int k)
{
	pthread_mutex_lock(&philo->data->l_meal);
	philo[k].last_meal = timestamp();
	pthread_mutex_unlock(&philo->data->l_meal);
	return (k - 1);
}

short int	philo(char **argv)
{
	int			k;
	t_env		env;
	t_data		data;

	env.data = &data;
	if (init_all(argv, &env) == 1)
		return (1);
	k = env.data->number_of_philosophers - 1;
	while (k > -1)
	{
		if (pthread_create(&env.philo[k].thread,
				NULL, philosopher, &env.philo[k]) != 0)
		{
			freer(&env);
			return (1);
		}
		k = set_last_meal(env.philo, k);
	}
	check(env.philo);
	freer(&env);
	return (0);
}
