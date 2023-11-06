/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:12:52 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/06 22:50:23 by hrahovha         ###   ########.fr       */
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
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] == ' ' || (argv[i][j] >= '0' && argv[i][j] <= '9'))
				;
			else
				return (1);
		}
	}
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
