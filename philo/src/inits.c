/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:29:26 by ltacos            #+#    #+#             */
/*   Updated: 2022/06/02 11:00:47 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_args(t_args *args, char **argv)
{
	args->num_philo = ft_atoi(argv[1]);
	args->time_die = ft_atoi(argv[2]);
	args->time_eat = ft_atoi(argv[3]);
	args->time_sleep = ft_atoi(argv[4]);
	args->num_meals = -1;
	if (argv[5] != NULL)
		args->num_meals = ft_atoi(argv[5]);
}

static t_mutex	*init_mutex_fork(int num_philo)
{
	t_mutex	*forks;
	int		i;

	i = 0;
	forks = (t_mutex *)malloc(sizeof(t_mutex) * num_philo);
	if (!forks)
		return (NULL);
	while (i < num_philo)
		pthread_mutex_init(&forks[i++], NULL);
	return (forks);
}

static t_filo	*init_filo(t_data *data, int num_filo)
{
	t_filo	*filo;
	int		i;

	i = 0;
	filo = (t_filo *)malloc(sizeof(t_filo) * num_filo);
	if (!filo)
		return (NULL);
	while (i < num_filo)
	{
		filo[i].id = i;
		filo[i].fork_l = (i + 1) % num_filo;
		filo[i].fork_r = i;
		filo[i].cur_num_meals = 0;
		filo[i].data = data;
		i++;
	}
	return (filo);
}

static pthread_t	*init_thread(int num_philo)
{
	pthread_t	*thread;

	thread = (pthread_t *)malloc(sizeof(pthread_t) * num_philo);
	if (!thread)
		return (NULL);
	return (thread);
}

int	init_data(t_data *data, char **argv)
{
	init_args(&data->args, argv);
	data->p_filo = init_filo(data, data->args.num_philo);
	if (!data->p_filo)
		return (0);
	data->p_forks = init_mutex_fork(data->args.num_philo);
	if (!data->p_forks)
		return (0);
	data->p_thread = init_thread(data->args.num_philo);
	if (!data->p_thread)
		return (0);
	pthread_mutex_init(&data->mutex_print, NULL);
	data->f_dead = 0;
	return (1);
}
