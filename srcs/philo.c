/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:37:35 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/04 12:47:00 by jalevesq         ###   ########.fr       */
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
	usleep((data->ms_sleep + data->ms_eat) / 2);
	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_mutex_destroy(&philo[i].fork_mutex);
		pthread_mutex_destroy(&philo[i].eat_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->printf_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->start_even_mutex);
	pthread_mutex_destroy(&data->start_odd_mutex);
}

int	ft_philo_all_eat(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_mutex_lock(&philo[i].eat_mutex);
		if (philo[i].eat_counter >= philo[i].must_eat)
		{
			pthread_mutex_unlock(&philo[i].eat_mutex);
			i++;
		}
		else
		{
			pthread_mutex_unlock(&philo[i].eat_mutex);
			return (0);
		}
	}

	return (1);
}

void	ft_check_state(t_philo *philo, t_data *data)
{
	int	i;

		while (1)
		{
			i = 0;
			while (i < data->philo_nbr)
			{
				pthread_mutex_lock(philo[i].death_mutex);
				if (*philo[i].is_dead == DEAD)
				{
					pthread_mutex_unlock(philo[i].death_mutex); 
					return ;
				}
				pthread_mutex_unlock(philo[i].death_mutex);
				if (ft_philo_all_eat(philo) == 1 && data->must_eat > 0)
				{
					pthread_mutex_lock(philo[i].death_mutex);
					*philo->finish_flag = FINISH;
					pthread_mutex_unlock(philo[i].death_mutex);
					return ;
				}
				i++;
			}
			usleep(5000);
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
		if(ft_atoi(av[5]) <= 0 || ft_atoi(av[5]) >= 2147483647)
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
