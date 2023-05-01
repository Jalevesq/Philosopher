/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:37:35 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/01 14:07:37 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_join_n_free(t_philo *philo, t_data *data)
{
    int i;

	i = 0;
    while (i < philo->philo_nbr)
    {
        pthread_join(data->philo[i], NULL);
        i++;
    }
	ft_usleep(data->ms_sleep + data->ms_eat);
	pthread_mutex_destroy(philo[i].printf_mutex);
	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_mutex_destroy(&philo[i].fork_mutex);
		pthread_mutex_destroy(&philo[i].start_mutex);
		pthread_mutex_destroy(&philo[i].death_mutex);
		i++;
	}
}

void	ft_check_state(t_philo *philo, t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			pthread_mutex_lock(&philo->death_mutex);
			if (*philo->is_dead == DEAD)
			{
				pthread_mutex_unlock(&philo->death_mutex);
				return ;
			}
			pthread_mutex_unlock(&philo->death_mutex);
			i++;
		}
	}
}

int	ft_check_arg(int ac, char **av)
{
	int i;
	int	j;

	j = 1;
	if (ac < 5 || ac > 6)
		return (1);
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
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) < 50 || ft_atoi(av[3]) < 50 || ft_atoi(av[4]) < 50)
		return (1);
	if (av[5])
	{
		if(ft_atoi(av[5]) <= 0)
			return (1);
	}
	return (0);
}

// -fsanitize=thread
// To do:
// 1- Start simulation time for every philosopher at the same time.
// 2- Wait for every thread to be created before starting.
int main(int ac, char **av)
{
    if (ft_check_arg(ac, av) == 1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	t_data *data;
	t_philo *philo;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	philo = malloc(sizeof(t_philo) * (atoi(av[1])));
	if (!philo)
		return (1);
	ft_init_philo(philo, data, av);
	ft_create_philo(philo, data, data->philo_nbr);
	ft_check_state(philo, data);
	ft_join_n_free(philo, data);
	free(data->philo);
	free(philo);
	free(data);
    return (0);
}
