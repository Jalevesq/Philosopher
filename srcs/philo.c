/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:37:35 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/24 19:10:15 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*ft_philosopher(void *arg)
{
	t_philo			*philo;
	// u_int64_t		philo_start;
	
	// Each philo will only count his last meal? (and own sleep with a ft_sleep?)
	philo = (t_philo *)arg;
	while (philo->flag != 1)
		;
	// gettimeofday(&time, NULL);
	// printf("%llu\n", (((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000))) - philo->start_ms);
	// printf("philo %d Simulation start\n", philo->philo_id);
	
	while (philo->flag != 2)
	{
		// gettimeofday(&philo->current, NULL);
		// pthread_mutex_lock(philo->fork_mutex);
		// philo->last_meal = (((philo->current.tv_sec * (uint64_t)1000) + (philo->current.tv_usec / 1000)) - philo->start_ms);
		// printf("%llu\n", philo->last_meal);
    	// pthread_mutex_unlock(philo->fork_mutex);
	}
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

void	ft_join_n_free(t_philo *philo)
{
    int i;
    int *status;

    i = 0;
    status = NULL;
    while (i < philo->philo_nbr)
    {
        pthread_join(philo[i].philo, (void *)status);
        pthread_mutex_destroy(philo[i].fork_mutex);
        i++;
    }
	i = 0;
	while (i < philo->philo_nbr)
	{
		free(philo[i].philo);
    	free(philo[i++].fork_mutex);
		i++;
	}
}

void	ft_check_health(t_philo *philo, t_data *data)
{
	int	i;
	int	j;
	struct timeval start;
	struct timeval time;

	u_int64_t begin;
	u_int64_t curr;

	gettimeofday(&start, NULL);
	begin = (start.tv_sec * (uint64_t)1000) + (start.tv_usec / 1000);
	while (1)
	{
		i = 0;
		gettimeofday(&time, NULL);
		curr = (time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000);
		printf("%llu\n", curr - begin);
		while (i < data->philo_nbr)
		{
			
			if (philo[i].last_meal >= data->ms_die)
			{
				j = 0;
				while (j < philo->philo_nbr)
				{
					philo[i].flag = 2;
					j++;
				}
				// usleep(10);
				printf("%llu ms - Philo %d died.\n", (((philo->current.tv_sec * (uint64_t)1000) + (philo->current.tv_usec / 1000))) - philo->start_ms, philo->philo_id);
				return ;
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
		// philo[i].ms_eat = data->ms_die;
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
		ft_join_n_free(philo);
		free(philo);
		free(data);
    }
    return (0);
}

		// if (philo->philo_id % 2 == 0)
		// {
		// 	pthread_mutex_lock(philo->fork_mutex);
		// 	if (philo->fork == ON_TABLE)
		// 	{
		// 		philo->fork == IN_USE_OWN;
		// 		printf("%llu ms - Philo %d prend sa fourchette.", (((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000))) - philo->start_ms, philo->philo_id);
		// 	}
		// 	if (philo->right_fork == ON_TABLE)
		// 	{
		// 		philo->fork = IN_USE;
		// 		printf("%llu ms - Philo %d prend la fourchette droite.", (((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000))) - philo->start_ms, philo->philo_id);
		// 	}
		// 	if (philo->fork == IN_USE_OWN && philo->right_fork == IN_USE)
		// 	{
		// 		printf("%llu ms - Philo %d mange...", (((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000))) - philo->start_ms, philo->philo_id);
		// 		usleep(philo.);
		// 		philo->fork = ON_TABLE;
		// 		philo->right_fork = ON_TABLE;
		// 	}
		// 	pthread_mutex_unlock(philo->fork_mutex);
		// }
		// else if (philo->philo_id % 3 == 0)
		// {
		// 	pthread_mutex_lock(philo->fork_mutex);
		// 	if (philo->fork == ON_TABLE)
		// 	{
		// 		philo->fork == IN_USE_OWN;
		// 		printf("%llu ms - Philo %d prend sa fourchette.", (((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000))) - philo->start_ms, philo->philo_id);
		// 	}
		// 	if (philo->right_fork == ON_TABLE)
		// 	{
		// 		philo->fork = IN_USE;
		// 		printf("%llu ms - Philo %d prend la fourchette droite.", (((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000))) - philo->start_ms, philo->philo_id);
		// 	}
		// 	if (philo->fork == IN_USE_OWN && philo->right_fork == IN_USE)
		// 	{
		// 		printf("%llu ms - Philo %d mange...", (((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000))) - philo->start_ms, philo->philo_id);
		// 		usleep(200 * 1000);
		// 		philo->fork = ON_TABLE;
		// 		philo->right_fork = ON_TABLE;
		// 	}
		// 	pthread_mutex_unlock(philo->fork_mutex);
		// }