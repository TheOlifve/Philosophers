/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:12:52 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/08 18:35:44 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	parser(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		if (!argv[i] || !*argv[i])
			return (1);
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				;
			else
				return (1);
		}
	}
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

int	err(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (err("ERROR - 1:Wrong number of parameters"));
	if (parser(argv) == 1)
		return (err("ERROR - 1:Wrong parameters"));
	if (load(&data, argc, argv))
		return (1);
	philo_create(&data);
	return (0);
}
