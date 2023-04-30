/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:27:26 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/30 14:10:01 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void	*ft_philosopher(void *arg)
{
	t_philo			*philo;
	
	philo = (t_philo *)arg;
	// Use to start every philosopher at the same time.
	pthread_mutex_lock(&philo->start_mutex);
	pthread_mutex_unlock(&philo->start_mutex);
	while (1)
	{

	}
	return (NULL);
}
	// gettimeofday(&curr, NULL);
	// now = ((curr.tv_sec * (uint64_t)1000)) + (curr.tv_usec / 1000);
	// printf("%llu\n", now - philo->start_ms);