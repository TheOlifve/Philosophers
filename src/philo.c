/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:26:54 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/08 17:10:14 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_forks(t_philo *philo)
{
	if (philo->id == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		msg(philo, "has taken a left fork");
		if (philo->data->ph_cnt == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
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
	my_sleep(philo->data, philo->data->eat_time);
	pthread_mutex_lock(&philo->t_lock);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->t_lock);
	return (0);
}

void	drop_forks(t_philo *philo)
{
	if (philo->id == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	pthread_mutex_lock(&philo->lock);
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->lock);
	msg(philo, "is sleeping");
	my_sleep(philo->data, philo->data->sleep_time);
}

int	eat(t_philo *philo)
{
	if (take_forks(philo))
		return (2);
	drop_forks(philo);
	msg(philo, "is thinking");
	if (philo->eat_cnt == philo->data->eat_cnt)
		return (1);
	return (0);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->d_lock);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->d_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->d_lock);
	return (0);
}

void	*philo_life(void *philo_data)
{	
	int		i;
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	if ((philo->id - 1) % 2)
		usleep(1000);
	while (is_dead(philo) == 0)
	{
		i = eat(philo);
		if (i == 1)
		{
			pthread_mutex_lock(&philo->data->we_lock);
			philo->data->was_eaten++;
			pthread_mutex_unlock(&philo->data->we_lock);
			break ;
		}
		else if (i == 2)
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
	while (1)
		if (dead_check(data, -1) == 1)
			break ;
	i = -1;
	while (++i < data->ph_cnt)
	{
		pthread_join(data->tid[i], 0);
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].lock);
		pthread_mutex_destroy(&data->philo[i].t_lock);
	}
	pthread_mutex_destroy(&data->print);
	return (0);
}
