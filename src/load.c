/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:02:28 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/04 16:20:54 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	fork_init(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->philo_amt)
	{
		if (pthread_mutex_init(&data->forks[i], 0))
			return (1);
		i++;
	}
	data->philo[0].r_fork = data->forks[0];
	data->philo[0].l_fork = data->forks[data->philo_amt - 1];
	i = 1;
	while (i < data->philo_amt)
	{
		data->philo[i].r_fork = data->forks[i];
		data->philo[i].l_fork = data->forks[i - 1];
		i++;
	}
	return (0);
}

int	philo_init(t_data *d)
{
	int	i;

	i = 0;
	while(i < d->philo_amt)
	{
		d->philo->t_id = malloc(sizeof(pthread_t));
		if (!d->philo->t_id)
			return (1);
		d->philo[i].id = i + 1;
		d->philo[i].die_time = get_time() + d->die_time;
		d->philo[i].data = d;
		i++;
	}
	return (0);
}

int	data_init(t_data *d, int argc, char **argv)
{
	d->dead = 0;
	d->philo_amt = ft_atoi(argv[1]);
	d->die_time = ft_atoi(argv[2]) * 1000;
	d->eat_time = ft_atoi(argv[3]) * 1000;
	d->sleep_time = ft_atoi(argv[4]) * 1000;
	pthread_mutex_init(&d->lock, 0);
	pthread_mutex_init(&d->print, 0);
	d->tid = malloc(sizeof(pthread_t));
	if (argc == 6)
		d->eat_amt = ft_atoi(argv[5]);
	else
		d->eat_amt = -1;
	d->philo = malloc(sizeof(t_philo) * d->philo_amt);
	if (!d->philo)
		return (1);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->philo_amt);
	if (!d->forks)
		return (1);
	return (0);
}

int	load(t_data *d, int argc, char **argv)
{
	if (data_init(d, argc, argv) == 1)
		return (err("ERROR - 2:Memory allocation failed"));
	if (fork_init(d) == 1)
		return (err("ERROR - 3:Mutex init failed"));
	if (philo_init(d) == 1)
		return (1);
	philo_create(d);
	return (0);
}