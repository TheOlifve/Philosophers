/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:44:22 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/22 16:12:23 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eat_cnt;
	long long		last_eat;
	pthread_mutex_t	lock;
	pthread_mutex_t	t_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				ph_cnt;
	int				eat_cnt;
	int				is_dead;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				was_eaten;
	t_philo			*philo;
	pthread_t		*tid;
	long long		start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	d_lock;
	pthread_mutex_t	we_lock;
	pthread_mutex_t	*forks;
}	t_data;

int			err(char *str);
int			is_dead(t_philo *philo);
int			ft_atoi(const char *str);
int			philo_create(t_data *data, int i);
int			load(t_data *data, int argc, char **argv);
int			dead_check(t_data *data, int i, int check);
void		my_sleep(t_data *data, int time);
void		msg(t_philo *philo, char *str);
long long	get_time(void);

#endif