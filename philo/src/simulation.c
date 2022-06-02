/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:07:05 by ltacos            #+#    #+#             */
/*   Updated: 2022/06/02 12:48:46 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	print_sleep(t_filo *filo, t_data *data)
{
	if (data->f_dead != 1)
	{
		print_log(MSG_SLEEP, filo, data);
		u_sleep(data->args.time_sleep);
		print_log(MSG_THINK, filo, data);
	}
}

static void	*one_filo(t_filo *filo)
{
	pthread_mutex_lock(&filo->data->p_forks[filo->fork_r]);
	print_log(MSG_FORK, filo, filo->data);
	pthread_mutex_unlock(&filo->data->p_forks[filo->fork_r]);
	return (NULL);
}

static void	get_fork_print(t_data *data, t_filo *filo, int num)
{
	if (data->f_dead != 1)
	{
		pthread_mutex_lock(&data->p_forks[num]);
		print_log(MSG_FORK, filo, data);
	}
}

static void	*simulation(void *ptr)
{
	t_filo	*filo;
	t_data	*data;

	filo = (t_filo *)ptr;
	data = filo->data;
	if (data->args.num_philo == 1)
		return (one_filo(filo));
	if (filo->id % 2)
		usleep(150);
	while (!data->f_dead)
	{
		if (data->args.num_meals != -1 && \
			!(filo->cur_num_meals < data->args.num_meals))
			break ;
		get_fork_print(data, filo, filo->fork_r);
		get_fork_print(data, filo, filo->fork_l);
		print_log(MSG_EAT, filo, data);
		filo->time_update = get_cur_time();
		u_sleep(data->args.time_eat);
		pthread_mutex_unlock(&data->p_forks[filo->fork_l]);
		pthread_mutex_unlock(&data->p_forks[filo->fork_r]);
		filo->cur_num_meals++;
		print_sleep(filo, data);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	t_filo		*filo;
	pthread_t	*thread;
	int			i;

	i = 0;
	thread = data->p_thread;
	filo = data->p_filo;
	data->time = get_cur_time();
	while (i < data->args.num_philo)
	{
		filo[i].data = data;
		if (pthread_create(&thread[i], NULL, simulation, (void *) &filo[i]))
			return (0);
		filo[i].time_update = get_cur_time();
		i++;
	}
	return (1);
}
