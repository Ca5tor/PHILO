/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:40:51 by ltacos            #+#    #+#             */
/*   Updated: 2022/06/02 12:47:31 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *str)
{
	int		flag;
	long	num;

	flag = 1;
	num = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if ((*str == '+' || *str == '-'))
	{
		if (*str == '-')
			flag = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*(str++) - 48);
		if (num > 2147483647 && flag == 1)
			return (-1);
		if (num > 2147483648 && flag == -1)
			return (0);
	}
	return (num * flag);
}

long	get_cur_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	print_log(char *msg, t_filo *filo, t_data *data)
{
	if (!data->f_dead)
	{
		pthread_mutex_lock(&data->mutex_print);
		printf(msg, (get_cur_time() - data->time), filo->id + 1);
		pthread_mutex_unlock(&data->mutex_print);
	}
}

void	u_sleep(long time)
{
	long	temp;

	temp = get_cur_time();
	while (get_cur_time() - temp < time)
		usleep(time / 10);
}
