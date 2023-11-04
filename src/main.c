/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:12:52 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/01 22:38:25 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	parser(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i] && argv[i][j])
	{
		if ((argv[i][j] != ' ') ||
			(argv[i][j] >= 48 && argv[i][j] <= 57))
			;
		else
			return (1);
		i++;
		j++;
	}
	while (i < 5)
	{
		if (ft_atoi(argv[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc < 5 || argc > 6)
		return (err("ERROR - 1:Wrong number of parameters"));
	if (parser(argv) == 1)
		return (err("ERROR - 1:Parameters can't be negative"));
	if (load(&data, argc, argv) == 1)
		return (1);
	// int i = get_time();
		// printf("%lld\n",get_time());
		// usleep(1000000);
		// printf("%lld\n",get_time());
	// while (1)
	// {
	// }
	return (0);
}

// void	*test1(void *data)
// {
// 	t_data *d;

// 	d = data;
// 	printf("!\n");
// 	pthread_mutex_lock(&d->mutex);
// 	while (d->die_time <= 1000)
// 	{
// 		usleep(1000);
// 		d->die_time++;
// 		pthread_mutex_unlock(&d->mutex);
// 		pthread_mutex_lock(&d->mutex);
// 	}
// 	pthread_mutex_unlock(&d->mutex);
// 	return (0);
// }

// void	*test2(void *data)
// {
// 	t_data *d;

// 	d = data;
// 	pthread_mutex_lock(&d->mutex);
// 	while (d->die_time < 1000)
// 	{
// 		usleep(999);
// 		printf("%d\n",d->die_time);
// 		pthread_mutex_unlock(&d->mutex);
// 		pthread_mutex_lock(&d->mutex);
// 	}
// 	return (0);
// }

// int	main(void)
// {
// 	t_data	data;
// 	pthread_t		p_id2 = 0;

// 	data.die_time = 0;
// 	pthread_mutex_init(&data.mutex, 0);
// 	pthread_create(&data.p_id, 0, test1, &data);
// 	pthread_create(&p_id2, 0, test2, &data);
// 	// pthread_mutex_lock(&data.mutex);
// 	// while (data.die_time < 1000)
// 	// {
// 	// 	usleep(100);
// 	// 	printf("%d\n",data.die_time);
// 	// 	// pthread_mutex_unlock(&data.mutex);
// 	// 	// pthread_mutex_lock(&data.mutex);
// 	// }
// 	// pthread_mutex_unlock(&data.mutex);
// 	pthread_join(p_id2, 0);
// 	pthread_join(data.p_id, 0);
// 	return (0);
// }