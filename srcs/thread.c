/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:27:26 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/27 18:41:12 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	ft_printf(t_philo *philo, char *str)
// {

// }

// void	ft_take_fork_n_eat(t_philo *philo)
// {

// }

void	ft_printf(t_philo *philo, char *str)
{
	struct timeval curr;
	uint64_t current;

	gettimeofday(&curr, NULL);
	current = ((curr.tv_sec * (uint64_t)1000)) + (curr.tv_usec / 1000);
	pthread_mutex_lock(philo->etat_mutex);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(philo->etat_mutex);
		return ;
	}		
	else
		printf("%llu ms - Philo %d %s\n", current - philo->start_ms, philo->philo_id, str);
	pthread_mutex_unlock(philo->etat_mutex);
}

void	*ft_philosopher(void *arg)
{
	struct timeval	current;
	struct timeval	meal;
	uint64_t		curr;
	t_philo			*philo;
	
	philo = (t_philo *)arg;
	
	// Use to start every philosopher at the same time.
	pthread_mutex_lock(philo->etat_mutex);
	if (philo->philo_id % 2 == 0)
		usleep(philo->ms_eat * 1000);
	pthread_mutex_unlock(philo->etat_mutex);
	pthread_mutex_lock(philo->fork_mutex);
	while (philo->state != DEAD)
	{
		pthread_mutex_unlock(philo->fork_mutex);
		gettimeofday(&meal, NULL);
		philo->last_meal = ((meal.tv_sec * (uint64_t)1000)) + (meal.tv_usec / 1000);
		pthread_mutex_lock(philo->fork_mutex);
		ft_printf(philo, "is eating");
		usleep(philo->ms_eat * 1000);
		gettimeofday(&current, NULL);
		curr = ((current.tv_sec * (uint64_t)1000)) + (current.tv_usec / 1000);
		// printf("philo %d - ms %llu\n", philo->philo_id, curr - philo->last_meal);
		if (curr - philo->last_meal >= philo->ms_die)
		{
			pthread_mutex_lock(philo->etat_mutex);
			philo->state = FIRST_DEAD;
			pthread_mutex_unlock(philo->etat_mutex);
			ft_printf(philo, "has died.");
			pthread_mutex_unlock(philo->fork_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(philo->fork_mutex);
		pthread_mutex_lock(philo->fork_mutex);
	}
	pthread_mutex_unlock(philo->fork_mutex);
	return (NULL);
}
		// gettimeofday(&current, NULL);
		// curr = ((current.tv_sec * (uint64_t)1000)) + (current.tv_usec / 1000);
		// printf("philo %d - %llu ms\n", philo->philo_id, curr - philo->start_ms);