/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:30:50 by ybendavi          #+#    #+#             */
/*   Updated: 2022/05/23 18:15:44 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	die(t_philo *philo, char d)
{
	pthread_mutex_lock(&philo->data->a_death);
	philo->data->death = 0;
	pthread_mutex_unlock(&philo->data->a_death);
	if (d == 0)
	{
		philo->data->all_death = philo->id;
		philo->data->death_time = timestamp();
	}
}

short int	has_eat(t_philo *philo)
{
	short int	i;

	i = philo->data->number_of_philosophers;
	if (philo->data->number_of_times_each_philosopher_must_eat == -1)
		return (1);
	i--;
	while (i > -1)
	{
		pthread_mutex_lock(&philo->data->a_eat);
		if (philo[i].eat_count
			< philo->data->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_unlock(&philo->data->a_eat);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->a_eat);
		i--;
	}
	die(philo, 1);
	return (0);
}

short int	death_checker(t_philo *philo)
{	
	unsigned int	d;

	pthread_mutex_lock(&philo->data->l_meal);
	d = timestamp() - philo->last_meal;
	pthread_mutex_unlock(&philo->data->l_meal);
	if (d >= philo->data->time_to_die)
	{
		die(philo, 0);
		return (0);
	}
	return (1);
}

short int	check(t_philo *philo)
{
	short int	i;
	short int	k;

	k = philo->data->number_of_philosophers - 1;
	while (has_eat(philo))
	{
		i = k;
		while (i > -1)
		{
			if (death_checker(&philo[i]) == 0)
				return (0);
			i--;
		}
	}
	return (0);
}
