/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:27:26 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/27 17:00:45 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	ft_printf(t_philo *philo, char *str)
// {

// }

// void	ft_take_fork_n_eat(t_philo *philo)
// {

// }

void	*ft_philosopher(void *arg)
{
	struct timeval	current;
	uint64_t		curr;
	t_philo			*philo;
	int				i;
	
	i = 0;
	philo = (t_philo *)arg;
	
	pthread_mutex_lock(philo->etat_mutex);
	pthread_mutex_unlock(philo->etat_mutex);
	while (1)
	{
		gettimeofday(&current, NULL);
		curr = ((current.tv_sec * (uint64_t)1000)) + (current.tv_usec / 1000);
		printf("philo %d - %llu ms\n", philo->philo_id, curr - philo->start_ms);
	}
	return (NULL);
}