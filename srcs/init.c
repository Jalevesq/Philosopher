/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:26:41 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/28 10:11:32 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_init_right_fork(t_philo *philo, int philo_nbr)
{
	int i;

	i = 0;
	while (i < philo_nbr)
	{
		if (i == 0)
		{
			philo[i].right_fork = &philo[philo_nbr - 1].fork;
			philo[i].right_fork_mutex = philo[philo_nbr - 1].fork_mutex;
		}
		else
		{
			philo[i].right_fork = &philo[i - 1].fork;
			philo[i].right_fork_mutex = philo[i - 1].fork_mutex;
		}
		i++;
	}
}

void	ft_init_philo(t_philo *philo, t_data *data, char **av)
{
	int	i;

	i = 0;
	data->philo_nbr = ft_atoi(av[1]);
	data->ms_die = ft_atoi(av[2]);
	data->ms_eat = ft_atoi(av[3]);
	data->ms_sleep = ft_atoi(av[4]);
	data->philo = malloc(sizeof(pthread_t) * data->philo_nbr);
	// if (av[5])
	// data->must_eat = ft_atoi(av[5]);
	// else
	// data->must_eat = -1;
	while (i < data->philo_nbr)
	{
		philo[i].philo_id = i + 1;
		philo[i].last_meal = 0;
		philo[i].state = THINKING;
		philo[i].ms_die = data->ms_die;
		philo[i].ms_eat = data->ms_eat;
		philo[i].ms_sleep = data->ms_sleep;
		philo[i].eat_counter = 0;
		philo[i].fork = ON_TABLE;
		// put malloc protection
		philo[i].fork_mutex = malloc(sizeof(pthread_mutex_t));
		philo[i].etat_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].fork_mutex, NULL);
		pthread_mutex_init(philo[i].etat_mutex, NULL);
		i++;
	}
	ft_init_right_fork(philo, data->philo_nbr);
}

void	ft_create_philo(t_philo *philo, t_data *data, int philo_nbr)
{
	int	i;
	struct timeval start;

	i = 0;
	while (i < philo_nbr)
		pthread_mutex_lock(philo[i++].etat_mutex);
	gettimeofday(&start, NULL); 
	i = 0;
	while (i < philo_nbr)
	{
		philo[i].start_ms = ((start.tv_sec * (uint64_t)1000)) + (start.tv_usec / 1000);
		pthread_create(&data->philo[i], NULL, ft_philosopher, &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo_nbr)
		pthread_mutex_unlock(philo[i++].etat_mutex);
}