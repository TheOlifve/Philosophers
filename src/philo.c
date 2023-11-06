/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:26:54 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/06 23:55:24 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		msg(philo, "has taken a left fork");
		pthread_mutex_lock(philo->right_fork);
		msg(philo, "has taken a right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		msg(philo, "has taken a right fork");
		pthread_mutex_lock(philo->left_fork);
		msg(philo, "has taken a left fork");
	}
	msg(philo, "is eating");
	my_sleep(philo->data->eat_time);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	msg(philo, "is sleeping");
	my_sleep(philo->data->sleep_time);
}

int	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->lock);
	philo->eat_cnt++;
	philo->time_left = get_time() + philo->data->die_time;
	pthread_mutex_unlock(&philo->data->lock);
	drop_forks(philo);
	msg(philo, "is thinking");
	if (philo->eat_cnt == philo->data->eat_cnt)
			return (1);
	return (0);
}

void	*philo_life(void *philo_data)
{	
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	if ((philo->id - 1) % 2)
		usleep(3000);
	while (philo->data->is_dead == 0)
		if (eat(philo))
		{
			philo->data->was_eaten++;
			break ;
		}
	return (0);
}

int	philo_create(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->ph_cnt)
		if (pthread_create(&data->tid[i], NULL, philo_life,
			&data->philo[i]))
			return (1);
	dead_check(data, 0 ,0);
	i = -1;
	while (++i < data->ph_cnt)
		pthread_join(data->tid[i], 0);
	i = -1;
	while (++i < data->ph_cnt)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->lock);
	return (0);
}
