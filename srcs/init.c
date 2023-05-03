/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:26:41 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/03 10:36:27 by jalevesq         ###   ########.fr       */
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
			philo[i].right_fork_mutex = &philo[philo_nbr - 1].fork_mutex;
		}
		else
		{
			philo[i].right_fork = &philo[i - 1].fork;
			philo[i].right_fork_mutex = &philo[i - 1].fork_mutex;
		}
		i++;
	}
}

void	ft_init_philo(t_philo *philo, t_data *data, char **av)
{
	int	i;

	i = 0;
	data->is_dead = NOT_DEAD;
	data->finish_flag = NOT_FINISH;
	data->philo_nbr = ft_atoi(av[1]);
	data->ms_die = ft_atoi(av[2]);
	data->ms_eat = ft_atoi(av[3]);
	data->ms_sleep = ft_atoi(av[4]);
	data->philo = malloc(sizeof(pthread_t) * data->philo_nbr);
	pthread_mutex_init(&data->printf_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->start_even_mutex, NULL);
	pthread_mutex_init(&data->start_odd_mutex, NULL);
	while (i < data->philo_nbr)
	{
		philo[i].eat_counter = 0;
		philo[i].philo_id = i + 1;
		philo[i].last_meal = 0;
		philo[i].finish_flag = &data->finish_flag;
		philo[i].is_dead = &data->is_dead;
		philo[i].state = THINKING;
		philo[i].philo_nbr = data->philo_nbr;
		philo[i].ms_die = data->ms_die;
		philo[i].ms_eat = data->ms_eat;
		philo[i].ms_sleep = data->ms_sleep;
		philo[i].must_eat = data->must_eat;
		philo[i].fork = ON_TABLE;
		philo[i].printf_mutex = &data->printf_mutex;
		philo[i].death_mutex = &data->death_mutex;
		philo[i].start_odd_mutex = &data->start_odd_mutex;
		philo[i].start_even_mutex = &data->start_even_mutex;
		// put malloc protection
		pthread_mutex_init(&philo[i].fork_mutex, NULL);
		pthread_mutex_init(&philo[i].eat_mutex, NULL);
		i++;
	}
	ft_init_right_fork(philo, data->philo_nbr);
}

void	ft_create_philo(t_philo *philo, t_data *data, int philo_nbr)
{
	int	i;
	uint64_t now;

	i = 0;
	pthread_mutex_lock(&data->start_even_mutex);
	pthread_mutex_lock(&data->start_odd_mutex);
	i = 0;
	now = get_time();
	while (i < philo_nbr)
	{
		philo[i].start_ms = now;
		philo[i].last_meal = now; 
		if (philo[i].philo_id % 2 == 0)
			pthread_create(&data->philo[i], NULL, ft_philosopher_even, &philo[i]);
		else
			pthread_create(&data->philo[i], NULL, ft_philosopher_odd, &philo[i]);
		i++;
	}
	pthread_mutex_unlock(&data->start_even_mutex);
	ft_usleep(philo, philo->ms_eat); // wont work if ms_eat or ms_sleep > ms_die. Add flag systen ? (if 1, dont look at philo)
	pthread_mutex_unlock(&data->start_odd_mutex);
}