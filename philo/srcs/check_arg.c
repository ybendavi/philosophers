/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:31:04 by ybendavi          #+#    #+#             */
/*   Updated: 2022/05/23 21:28:48 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

short int	zero_checker(char *str, short int index)
{
	short int	i;

	i = 0;
	if (!str)
	{
		printf("Wrong arguments!\n");
		return (0);
	}
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] == 0)
	{
		if (index == 0)
		{
			printf("No philosopher around the table!\n");
			return (0);
		}
	}
	return (1);
}

short int	check_arg(char **argv)
{
	short int	i;
	short int	j;

	j = 0;
	while (argv[j])
	{
		i = 0;
		if (zero_checker(argv[j], j) == 0)
			return (0);
		while (argv[j][i])
		{
			if (argv[j][i] > '9' || argv[j][i] < '0')
			{
				printf("Wrong Arguments\n");
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}
