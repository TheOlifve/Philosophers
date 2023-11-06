/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:41:06 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/06 23:52:55 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	my_sleep(int time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		;
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
	if (philo->data->is_dead == 0)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%lld ms %d %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->data->print);
	}
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

void	dead_check(t_data *data, int i, long long test)
{
	while (data->is_dead == 0)
	{
		i = -1;
		while (++i < data->ph_cnt)
		{
			test = get_time();
			pthread_mutex_lock(&data->lock);
			if (test >= data->philo[i].time_left)
			{
				data->is_dead = 1;
				pthread_mutex_lock(&data->print);
				printf("%lld ms %d died\n", (test - data->start_time),
				data->philo[i].id);
				pthread_mutex_unlock(&data->lock);
				break ;
			}
			else if (data->ph_cnt == data->was_eaten)
			{
				data->is_dead = 1;
				break ;
			}
			pthread_mutex_unlock(&data->lock);
		}
	}
}
