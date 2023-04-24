/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:37:35 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/24 15:49:02 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*ft_philosopher(void *arg)
{
	t_philo			*philo;
	// u_int64_t		philo_start;
	struct timeval time;
	
	// Create start time at the same time for every philo.
	// Each philo will only count his last meal? (and own sleep with a ft_sleep?)
	philo = (t_philo *)arg;
	while (philo->flag != 1)
		;
	gettimeofday(&time, NULL);
	printf("%llu\n", (((time.tv_sec * (uint64_t)1000)) + (time.tv_usec / 1000)) - philo->start_ms);
	// printf("philo %d Simulation start\n", philo->philo_id);
	
	// while (philo->flag != 2)
	// {
	// }
	return (NULL);
}

void	ft_create_philo(t_philo *philo, int philo_nbr)
{
	int	i;
	struct timeval start;

	i = 0;
	gettimeofday(&start, NULL);
	while (i < philo_nbr)
	{
		philo[i].start_ms = (start.tv_sec * (uint64_t)1000) + (start.tv_usec / 1000);
		pthread_create(&philo[i].philo, NULL, ft_philosopher, &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo_nbr)
		philo[i++].flag = 1;
}

void	ft_check_health(t_philo *philo, t_data *data)
{
	int	i;
	// struct timeval start;
	// struct timeval time;

	// u_int64_t begin;
	// u_int64_t curr;

	// gettimeofday(&start, NULL);
	// begin = (start.tv_sec * (uint64_t)1000) + (start.tv_usec / 1000);
	while (1)
	{
		i = 0;
		// gettimeofday(&time, NULL);
		// curr = (time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000);
		// printf("%llu\n", curr - begin);
		while (i < data->philo_nbr)
		{
			
			if (philo[i].last_meal >= data->ms_die)
			{
				// while (j < philo_nbr) set philo flag to 2.
				// ft_join_n_exit() func to join all thread and free, stop thread and leave.
			}
			i++;
		}
	}
}

void	ft_init_right_fork(t_philo *philo, int philo_nbr)
{
	int i;

	i = 0;
	while (i < philo_nbr)
	{
		if (i == 0)
			philo[i].right_fork = &philo[philo_nbr - 1].fork;
		else
			philo[i].right_fork = &philo[i - 1].fork;
		i++;
	}
}

void	ft_init_philo(t_philo *philo, t_data *data, char **av)
{
	int	i;

	i = 0;
	data->philo_nbr = ft_atoi(av[1]);
	data->ms_die = ft_atoi(av[2]);
	// data->ms_eat = ft_atoi(av[3]);
	// data->ms_sleep = ft_atoi(av[4]);
	// if (av[5])
	// data->must_eat = ft_atoi(av[5]);
	// else
	// data->must_eat = -1;
	while (i < data->philo_nbr)
	{
		philo[i].philo_id = i + 1;
		philo[i].last_meal = 0;
		philo[i].eat_counter = 0;
		philo[i].flag = -1;
		philo[i].fork = ON_TABLE;
		// put malloc protection
		philo[i].philo = malloc(sizeof(pthread_t));
		philo[i].fork_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].fork_mutex, NULL);
		i++;
	}
	ft_init_right_fork(philo, data->philo_nbr);
}

// To do:
// 1- Start simulation time for every philosopher at the same time.
// 2- Wait for every thread to be created before starting.
int main(int ac, char **av)
{
    (void)ac;
    if (ac > 1)
    {
        t_data *data;
		t_philo *philo;

        data = malloc(sizeof(t_data));
        if (!data)
            return (1);
		philo = malloc(sizeof(t_philo) * (atoi(av[1])));
		if (!philo)
			return (1);
        ft_init_philo(philo, data, av);
		ft_create_philo(philo, data->philo_nbr);
		ft_check_health(philo, data);
		
    }
    return (0);
}