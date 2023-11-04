/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:26:54 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/04 16:15:16 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*dead_check(void *philo_data)
{
	t_philo		*philo;

	philo = (t_philo *)philo_data;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->data->lock);
		printf("die_time - %lld\n", philo->die_time);
		printf("get_time - %lld\n", get_time());
		// usleep(1000000);
		if (get_time() >= philo->die_time)
		{
			philo->data->dead = 1;
			pthread_mutex_lock(&philo->data->print);
			printf("%lld ms %d died\n", (get_time() - philo->data->start_time) / 1000,
				philo->id);
			pthread_mutex_unlock(&philo->data->print);
			pthread_mutex_unlock(&philo->data->lock);
			return ((void *)1);
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
	return ((void *)0);
}

void	*philo_life(void *data)
{	
	t_philo	*philo;

	philo = (t_philo *)data;
	// philo->die_time = get_time() + philo->data->die_time;
	(void)philo;
	// printf("%d\n", philo->id);
	return (0);
}

int	philo_create(t_data *d)
{
	int	i;

	i = -1;
	d->start_time = get_time();
	printf("%d\n",d->philo_amt);
	if (d->eat_amt > 0 || d->philo_amt > 0)
			pthread_create(&d->tid, NULL, dead_check, &d->philo[0]);
	// while (++i < d->philo_amt)
	// {
	// 	if (pthread_create(&d->philo[i].t_id, NULL, philo_life, &d->philo[i]) == -1)
	// 		return (1);
	// }
	i = -1;
	// printf("!\n");
	pthread_join(d->tid, NULL);
	while (++i < d->philo_amt)
		pthread_join(d->philo[i].t_id, NULL);
	return (0);
}