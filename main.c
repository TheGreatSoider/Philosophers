/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:47:09 by cocheong          #+#    #+#             */
/*   Updated: 2023/10/02 16:47:09 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	case_one(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->thread_id[0],
			NULL, &routine, &data->philosophers[0]))
		return (error(TH_ERR, data));
	pthread_detach(data->thread_id[0]);
	while (data->dead == 0)
		gotosleep(0);
	ft_exit(data);
	return (0);
}

void	clear_data(t_data *data)
{
	if (data->thread_id)
		free(data->thread_id);
	if (data->forks)
		free(data->forks);
	if (data->philosophers)
		free(data->philosophers);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philosophers[i].lock);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	clear_data(data);
}

int	error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (arg_are_correct(ac, av))
	{
		if (init(&data, ac, av))
			return (1);
		if (data.no_of_philo == 1)
			return (case_one(&data));
		if (thread_init(&data))
			return (1);
		ft_exit(&data);
	}
	return (0);
}

// int	main(int ac, char **av)
// {
// 	t_data	data;

// 	if (arg_are_correct(ac, av))
// 	{
// 		init(&data, ac, av);
// 		if (data.no_of_philo == 1)
// 			return (case_one(&data));
// 		thread_init(&data);
// 		ft_exit(&data);
// 	}
// 	return (0);
// }
