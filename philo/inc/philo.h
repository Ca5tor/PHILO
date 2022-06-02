/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:57:08 by ltacos            #+#    #+#             */
/*   Updated: 2022/06/02 12:39:23 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

# define MSG_ERROR_ARG_0	"Error: Invalid num of args\n"
# define MSG_ERROR_ARG_1	"Error: Not valid arg\n"
# define MSG_ERROR_ARG_2	"Error: Too many philosophers\n"

# define MSG_FORK			"%d %d has taken a fork\n"
# define MSG_EAT			"%d %d is eating\n"
# define MSG_SLEEP			"%d %d is sleeping\n"
# define MSG_THINK			"%d %d is thinking\n"
# define MSG_DEAD			"%d %d died\n"

# define MAX_FILO 200

struct					s_data;

typedef struct s_args
{
	int	num_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_meals;
}	t_args;

typedef struct s_filo
{
	int				id;
	int				fork_l;
	int				fork_r;
	int				cur_num_meals;
	long			time_update;
	struct s_data	*data;
}	t_filo;

typedef struct s_data
{
	t_args			args;
	t_filo			*p_filo;
	t_mutex			*p_forks;
	pthread_t		*p_thread;
	t_mutex			mutex_print;
	unsigned int	f_dead;
	long			time;
}	t_data;

int		ft_atoi(const char *str);
int		init_data(t_data *data, char **argv);
int		start_simulation(t_data *data);
long	get_cur_time(void);
void	print_log(char *msg, t_filo *philo, t_data *data);
void	u_sleep(long time);

#endif