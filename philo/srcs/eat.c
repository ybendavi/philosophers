/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:07:12 by ybendavi          #+#    #+#             */
/*   Updated: 2022/05/23 20:35:51 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks_p2(t_philo *philo)
{	
	pthread_mutex_lock(&philo->data->fork[philo->right_fork_id]);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->fork[philo->left_fork_id]);
	print_message(philo, "has taken a fork");
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->data->fork[philo->left_fork_id]);
		print_message(philo, "has taken a fork");
		if (philo->left_fork_id == philo->right_fork_id)
		{
			pthread_mutex_lock(&philo->data->a_death);
			while (philo->data->death)
			{
				pthread_mutex_unlock(&philo->data->a_death);
				usleep(1000);
				pthread_mutex_lock(&philo->data->a_death);
			}
			pthread_mutex_unlock(&philo->data->a_death);
			philo->die = 0;
			return ;
		}
		pthread_mutex_lock(&philo->data->fork[philo->right_fork_id]);
		print_message(philo, "has taken a fork");
	}
	else
		take_forks_p2(philo);
}

void	give_back_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork_id]);
		if (philo->left_fork_id != philo->right_fork_id)
			pthread_mutex_unlock(&philo->data->fork[philo->left_fork_id]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork_id]);
		if (philo->left_fork_id != philo->right_fork_id)
			pthread_mutex_unlock(&philo->data->fork[philo->right_fork_id]);
	}
}

short int	eat(t_philo *philo)
{
	take_forks(philo);
	if (!philo->die)
	{
		give_back_forks(philo);
		return (1);
	}
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->data->l_meal);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->data->l_meal);
	sleep_step(philo, philo->data->time_to_eat);
	give_back_forks(philo);
	pthread_mutex_lock(&philo->data->a_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->a_eat);
	eval_rt(philo);
	return (0);
}
