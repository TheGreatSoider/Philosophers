/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:51:41 by cocheong          #+#    #+#             */
/*   Updated: 2023/10/13 17:48:57 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *data_p)
{
	t_philo	*philo;

	philo = (t_philo *) data_p;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->no_of_philo)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *) 0);
}

void	*supervisor(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *) philo_p;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->dead && philo->makaning == 0)
			print_message(DIED, philo);
		if (philo->eat_count == philo->data->no_of_makans)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_count++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *) 0);
}

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *) philo_p;
	if (philo->id % 2 == 0)
		gotosleep(1);
	philo->dead = philo->data->time_of_death + get_time();
	if (pthread_create(&philo->thread_id, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		makan(philo);
		print_message(THINKING, philo);
	}
	if (pthread_join(philo->thread_id, NULL))
		return ((void *) 1);
	return ((void *) 0);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	t0;

	i = 0;
	data->start_time = get_time();
	while (i < data->no_of_philo)
	{
		if (pthread_create(&data->thread_id[i], NULL,
				&routine, &data->philosophers[i]))
			return (error(TH_ERR, data));
		gotosleep(1);
		i++;
	}
	if (data->no_of_makans > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philosophers[0]))
			return (error(TH_ERR, data));
	}
	i = -1;
	while (++i < data->no_of_philo)
	{
		if (pthread_join(data->thread_id[i], NULL))
			return (error(TH_ERR, data));
	}
	return (0);
}
