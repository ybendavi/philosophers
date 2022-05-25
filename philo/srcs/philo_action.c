/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:18:05 by ybendavi          #+#    #+#             */
/*   Updated: 2022/05/24 15:02:46 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	sleep_step(t_philo *philo, unsigned int data)
{
	size_t	now;
	char	death;

	now = timestamp();
	pthread_mutex_lock(&philo->data->a_death);
	death = philo->data->death;
	pthread_mutex_unlock(&philo->data->a_death);
	if (!death)
		philo->die = 0;
	while (timestamp() < now + data)
	{
		pthread_mutex_lock(&philo->data->a_death);
		death = philo->data->death;
		pthread_mutex_unlock(&philo->data->a_death);
		if (!death)
		{
			philo->die = 0;
			break ;
		}
		usleep(1000);
	}
}

void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	sleep_step(philo, philo->data->time_to_sleep);
	eval_rt(philo);
}

short int	eat_condition(t_philo *philo)
{
	char	res;

	res = 1;
	if (philo->round_table == philo->id || (philo->round_table
			== philo->data->number_of_philosophers && philo->id == 1))
		res = 0;
	return (res);
}
