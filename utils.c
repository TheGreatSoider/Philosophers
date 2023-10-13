/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:47:20 by cocheong          #+#    #+#             */
/*   Updated: 2022/08/26 17:21:55 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long		i;
	long		nbr;
	int			is_neg;

	i = 0;
	nbr = 0;
	is_neg = 1;
	while (space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			is_neg = -1;
		i++;
	}
	while (str[i] != '\0' && is_numeric(str[i]))
	{
		nbr = (nbr * 10) + (str[i++] - '0');
		if (nbr * is_neg > 2147483647)
			return (-1);
		if (nbr * is_neg < -2147483648)
			return (0);
	}
	return (nbr * is_neg);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

int	gotosleep(useconds_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}
