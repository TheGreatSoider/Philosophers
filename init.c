/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:30:04 by cocheong          #+#    #+#             */
/*   Updated: 2023/10/04 18:30:04 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc(t_data *data)
{
	data->thread_id = malloc(sizeof(pthread_t) * data->no_of_philo);
	if (!data->thread_id)
		return (error(ALLOC_ERR_1, data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->no_of_philo);
	if (!data->forks)
		return (error(ALLOC_ERR_2, data));
	data->philosophers = malloc(sizeof(t_philo) * data->no_of_philo);
	if (!data->philosophers)
		return (error(ALLOC_ERR_3, data));
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->philosophers[0].left_fork = &data->forks[0];
	data->philosophers[0].right_fork = &data->forks[data->no_of_philo - 1];
	i = 1;
	while (i < data->no_of_philo)
	{
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philo)
	{
		data->philosophers[i].data = data;
		data->philosophers[i].id = i + 1;
		data->philosophers[i].dead = data->time_of_death;
		data->philosophers[i].eat_count = 0;
		data->philosophers[i].makaning = 0;
		data->philosophers[i].status = 0;
		pthread_mutex_init(&data->philosophers[i].lock, NULL);
		i++;
	}
}

int	init_data(t_data *data, int ac, char **av)
{
	data->no_of_philo = ft_atoi(av[1]);
	data->time_of_death = ft_atoi(av[2]);
	data->makan_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		data->no_of_makans = ft_atoi(av[5]);
	else
		data->no_of_makans = -1;
	if (data->no_of_philo <= 0 || data->no_of_philo > 200
		|| data->time_of_death < 0 || data->makan_time < 0
		|| data->sleep_time < 0)
		return (error(ERR_IN_2, NULL));
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int	init(t_data *data, int ac, char **av)
{
	if (init_data(data, ac, av))
		return (1);
	if (alloc(data))
		return (1);
	if (init_forks(data))
		return (1);
	init_philo(data);
	return (0);
}
