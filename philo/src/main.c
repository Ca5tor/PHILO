/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:11:39 by ltacos            #+#    #+#             */
/*   Updated: 2022/06/02 12:45:58 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static unsigned int	cheak_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc > 6 || argc < 5)
		return (0 * write(2, MSG_ERROR_ARG_0, 28));
	while (++i < argc)
		if (ft_atoi(argv[i]) <= 0)
			return (0 * write(2, MSG_ERROR_ARG_1, 22));
	if (ft_atoi(argv[1]) >= 200)
		return (0 * write(2, MSG_ERROR_ARG_2, 30));
	return (1);
}

static void	check_is_life(t_data *data, int i)
{
	t_filo	*filo;

	filo = data->p_filo;
	while (data->args.num_meals != 0)
	{
		i = 0;
		while (i < data->args.num_philo && !data->f_dead)
		{
			if ((get_cur_time() - filo[i].time_update) > data->args.time_die)
			{
				print_log(MSG_DEAD, &filo[i], data);
				data->f_dead = 1;
			}
			i++;
			usleep(100);
		}
		if (data->f_dead)
			break ;
		i = 0;
		while (i < data->args.num_philo && \
			filo[i].cur_num_meals >= data->args.num_meals)
			i++;
		if (i == data->args.num_philo && data->args.num_meals != -1)
			data->args.num_meals = 0;
	}
}

static void	un_init(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->args.num_philo)
		pthread_join(data->p_thread[i++], NULL);
	i = 0;
	while (i < data->args.num_philo)
		pthread_mutex_destroy(&data->p_forks[i++]);
	pthread_mutex_destroy(&data->mutex_print);
}

static void	free_strct(t_data *data)
{
	if (data->p_filo)
		free(data->p_filo);
	if (data->p_forks)
		free(data->p_forks);
	if (data->p_thread)
		free(data->p_thread);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!cheak_args(argc, argv))
		return (0);
	if (!init_data(&data, argv))
		return (free_strct(&data), 0);
	if (!start_simulation(&data))
		return (free_strct(&data), 0);
	check_is_life(&data, 0);
	un_init (&data);
	free_strct(&data);
	return (0);
}
