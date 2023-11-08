/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:41:06 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/08 18:31:07 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	my_sleep(t_data *data, int time)
{
	long long	start;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(&data->d_lock);
		if (get_time() - start >= time || data->is_dead)
			break ;
		pthread_mutex_unlock(&data->d_lock);
		usleep (50);
	}
	pthread_mutex_unlock(&data->d_lock);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	msg(t_philo *philo, char *str)
{
	long long	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->d_lock);
	if (philo->data->is_dead == 0)
	{
		pthread_mutex_unlock(&philo->data->d_lock);
		printf("%lld ms %d %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	pthread_mutex_unlock(&philo->data->d_lock);
	pthread_mutex_unlock(&philo->data->print);
}

int	ft_atoi(const char *str)
{
	unsigned char	*str1;
	int				neg;
	int				num;

	neg = 1;
	if (!str)
		return (0);
	str1 = (unsigned char *) str;
	while (((*str1 >= 9 && *str1 <= 13) || *str1 == ' '))
		str1++;
	if (*str1 == '-' || *str1 == '+')
	{
		if (*str1 == '-')
			neg = -neg;
		str1++;
	}
	if (*str1 < 48 && *str1 > 57)
		return (0);
	num = 0;
	while (*str1 >= 48 && *str1 <= 57)
	{
		num = num * 10 + (*str1 - 48);
		str1++;
	}
	return (num * neg);
}

int	dead_check(t_data *data, int i)
{
	while (++i < data->ph_cnt)
	{
		pthread_mutex_lock(&data->philo[i].t_lock);
		if (get_time() - data->philo[i].last_eat > data->die_time)
		{
			pthread_mutex_unlock(&data->philo[i].t_lock);
			pthread_mutex_lock(&data->d_lock);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->d_lock);
			pthread_mutex_lock(&data->print);
			printf("%lld ms %d died\n", (get_time() - data->start_time),
				data->philo[i].id);
			pthread_mutex_unlock(&data->print);
			return (1);
		}
		pthread_mutex_unlock(&data->philo[i].t_lock);
		pthread_mutex_lock(&data->we_lock);
		if (data->ph_cnt == data->was_eaten)
		{
			pthread_mutex_unlock(&data->we_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->we_lock);
	}
	return (0);
}
