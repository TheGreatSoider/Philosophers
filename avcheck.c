/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avcheck.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:33:42 by cocheong          #+#    #+#             */
/*   Updated: 2023/10/04 17:33:42 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_numeric(int count)
{
	if (count >= 48 && count <= 57)
		return (1);
	else
		return (0);
}

int	string_is_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_numeric(str[i]) == 0)
			return (0);
	}
	return (1);
}

int	all_args_are_numbers(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (!string_is_numeric(av[i]))
			return (0);
	}
	return (1);
}

int	no_arguments_outside_limits(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (ft_atoi(av[i]) > INT_MAX || ft_atoi(av[i]) < INT_MIN)
			return (0);
	}
	return (1);
}

int	arg_are_correct(int ac, char **av)
{
	int	i;

	i = 0;
	if ((ac == 5 || ac == 6) && all_args_are_numbers(av))
	{
		if (no_arguments_outside_limits(av))
			return (1);
		printf("Arguments reaches int limits\n");
		return (0);
	}
	printf("Invalid no. of arguments or contains negative value\n");
	return (0);
}
