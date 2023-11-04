/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:44:22 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/04 15:22:56 by hrahovha         ###   ########.fr       */
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
	long long		die_time;
	pthread_t		t_id;
	struct s_data	*data;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
}	t_philo;

typedef struct s_data
{
	int				dead;
	int				eat_amt;
	int				die_time;
	int				eat_time;
	int				philo_amt;
	int				sleep_time;
	t_philo			*philo;
	pthread_t		tid;
	long long		start_time;
	long long		time;
	pthread_mutex_t lock;
	pthread_mutex_t print;
	pthread_mutex_t *forks;
}	t_data;

int			ft_atoi(const char *str);
int			err(char *str);
int			load(t_data *d, int argc, char **argv);
int			philo_create(t_data *d);
long long	get_time(void);

# endif