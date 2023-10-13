/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:47:31 by cocheong          #+#    #+#             */
/*   Updated: 2023/10/11 17:47:31 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

//	alloc_err
# define ALLOC_ERR_1 "ERROR WHILE ALLOCATING THREADS IDs"
# define ALLOC_ERR_3 "ERROR WHILE ALLOCATING PHILOS"
# define ALLOC_ERR_2 "ERROR WHILE ALLOCATING FORKS"
//	input_err
# define ERR_IN_1 "INVALID INPUT CHARACTER"
# define ERR_IN_2 "INVALID INPUT VALUES"
//	pthread_err
# define TH_ERR "ERROR WHILE CREATING THREADS"
# define JOIN_ERR "ERROR WHILE JOINING THREADS"
# define INIT_ERR_1 "ERROR WHILE INIT FORKS"
//	time_err
# define TIME_ERR "UNABLE TO RETRIVE UTC"
//	philo_msg
# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

# define INT_MAX 2147483647
# define INT_MIN -2147483648

struct	s_data;

typedef struct s_philo
{
	int					id;
	int					eat_count;
	int					status;
	int					makaning;
	int					dead;
	pthread_t			thread_id;
	pthread_mutex_t		lock;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	int				no_of_philo;
	int				no_of_makans;
	int				finished;
	int				dead;
	uint64_t		time_of_death;
	uint64_t		makan_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	pthread_t		*thread_id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	t_philo			*philosophers;
}	t_data;

int		get_time(void);
void	makan(t_philo *philo);
void	print_message(char *str, t_philo *philo);
int		init(t_data *data, int ac, char **av);
int		thread_init(t_data *data);
void	*routine(void *philo_p);
int		ft_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);
int		gotosleep(useconds_t time);
int		is_numeric(int count);
int		arg_are_correct(int ac, char **av);
int		error(char *str, t_data *data);
void	ft_exit(t_data *data);

#endif