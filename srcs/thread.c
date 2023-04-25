/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:27:26 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/25 16:55:47 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// long long int	ft_get_time()
// {

// }

void	ft_printf(t_philo *philo)
{
	struct timeval current;
	u_int64_t now;

	pthread_mutex_lock(philo->fork_mutex);
	gettimeofday(&current, NULL);
	now = (current.tv_sec * (uint64_t)1000) + (current.tv_usec / 1000);
	printf("%llu ms - Philo %d is saying Hi !\n", now - philo->start_ms, philo->philo_id); // %llu ms - Philo %d %str
	pthread_mutex_unlock(philo->fork_mutex);
}

// void	ft_eat(t_philo *philo)
// {
	
// }

void	*ft_philosopher(void *arg)
{
	t_philo			*philo;
	
	// Each philo will only count his last meal? (and own sleep with a ft_sleep?)
	philo = (t_philo *)arg;
	// while (philo->flag != 1)
	// 	;
	// if (philo->philo_id % 2 == 0)
	// 	usleep(philo->ms_eat * 1000);
	ft_printf(philo);
	// ft_eat();
	// ft_sleep();
	// ft_think_until_can_eat();
	return (NULL);
}