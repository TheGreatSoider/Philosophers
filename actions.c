/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:58:56 by cocheong          #+#    #+#             */
/*   Updated: 2023/10/02 16:58:56 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	print_message(char *str, t_philo *philo)
{
	uint64_t	t;

	pthread_mutex_lock(&philo->data->write);
	t = get_time() - philo->data->start_time;
	if (ft_strcmp(DIED, str) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", t, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", t, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message(TAKE_FORKS, philo);
	pthread_mutex_lock(philo->left_fork);
	print_message(TAKE_FORKS, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(SLEEPING, philo);
	gotosleep(philo->data->sleep_time);
}

void	makan(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->makaning = 1;
	philo->dead = get_time() + philo->data->time_of_death;
	print_message(EATING, philo);
	philo->eat_count++;
	gotosleep(philo->data->makan_time);
	philo->makaning = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
