/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:44:22 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/06 21:10:50 by hrahovha         ###   ########.fr       */
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
	long long		time_left;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				ph_cnt;
	int				eat_cnt;
	int				is_dead;
	int				was_eaten;
	t_philo			*philo;
	long long		die_time;
	long long		eat_time;
	long long		start_time;
	long long		sleep_time;
	pthread_mutex_t	lock;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_t		*tid;
}	t_data;

int			ft_atoi(const char *str);
int			err(char *str);
int			load(t_data *data, int argc, char **argv);
int			philo_create(t_data *data);
void		msg(t_philo *philo, char *str);
void		dead_check(t_data *data, int i, long long test);
long long	get_time(void);

# endif