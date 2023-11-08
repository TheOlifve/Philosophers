/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:02:28 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/08 15:43:23 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	fork_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->ph_cnt)
	{
		if (pthread_mutex_init(&data->forks[i], 0))
			return (1);
	}
	i = 0;
	data->philo[0].right_fork = &data->forks[0];
	data->philo[0].left_fork = &data->forks[data->ph_cnt - 1];
	while (++i < data->ph_cnt)
	{
		data->philo[i].right_fork = &data->forks[i];
		data->philo[i].left_fork = &data->forks[i - 1];
	}
	return (0);
}

int	philo_init(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->ph_cnt)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_cnt = 0;
		data->philo[i].last_eat = get_time();
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].lock, NULL);
		pthread_mutex_init(&data->philo[i].t_lock, NULL);
		i++;
	}
	return (0);
}

int	data_init(t_data *data, int argc, char **argv)//err - 1(Params), 2(Malloc)
{
	data->is_dead = 0;
	data->was_eaten = 0;
	data->ph_cnt = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);//in milliseconds
	data->eat_time = ft_atoi(argv[3]);//in milliseconds
	data->sleep_time = ft_atoi(argv[4]);//in milliseconds
	data->eat_cnt = -1;
	if (argc == 6)
		data->eat_cnt = ft_atoi(argv[5]);
	if (data->ph_cnt < 1 || data->eat_cnt == 0)
		return (1);
	if (data->die_time < 0 || data->eat_time < 0 || data->sleep_time < 0)
		return (1);
	data->start_time = get_time();//in milliseconds
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->d_lock, NULL);
	pthread_mutex_init(&data->we_lock, NULL);
	data->tid = malloc(sizeof(pthread_t) * data->ph_cnt);
	data->philo = malloc(sizeof(t_philo) * data->ph_cnt);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->ph_cnt);
	if (!data->tid || !data->forks || !data->philo)
		return (2);
	return (0);
}

int	load(t_data *data, int argc, char **argv)
{
	int	data_check;
	
	data_check = data_init(data, argc, argv);
	if (data_check == 1)
		return (err("ERROR - 1:Wrong parameters"));
	else if (data_check == 2)
		return (err("ERROR - 2:Memory allocation failed"));
	philo_init(data);
	if (fork_init(data))
		return (err("ERROR - 3:Mutex init failed"));
	return (0);
}
