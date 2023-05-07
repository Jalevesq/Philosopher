/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:24:22 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/07 11:30:37 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static	int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
		return (i);
	}
	return (i);
}

static int	ft_check_digit_input(char **av)
{
	int	i;
	int	j;

	j = 1;
	while (av[j] && j < 6)
	{
		i = 0;
		while (av[j][i])
		{
			if (ft_isdigit(av[j][i]) == 0)
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

static int	ft_amount_in_input(char **av)
{
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) >= 351
		|| ft_atoi(av[2]) < 50 || ft_atoi(av[2]) >= 2147483647
		|| ft_strlen(av[2]) >= 11
		|| ft_atoi(av[3]) < 50 || ft_atoi(av[3]) >= 2147483647
		|| ft_strlen(av[3]) >= 11
		|| ft_atoi(av[4]) < 50 || ft_atoi(av[4]) >= 2147483647
		|| ft_strlen(av[4]) >= 11)
		return (1);
	if (av[5])
	{
		if (ft_atoi(av[5]) <= 0 || ft_atoi(av[5]) >= 2147483647
			|| ft_strlen(av[5]) >= 11)
			return (1);
	}
	return (0);
}

int	ft_check_arg(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (1);
	if (ft_check_digit_input(av) == 1)
		return (1);
	if (ft_amount_in_input(av) == 1)
		return (1);
	return (0);
}
