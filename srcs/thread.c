/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:27:26 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/27 21:04:43 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_printf(t_philo *philo, char *str)
{
	struct timeval curr;
	uint64_t current;

	gettimeofday(&curr, NULL);
	current = ((curr.tv_sec * (uint64_t)1000)) + (curr.tv_usec / 1000);
	pthread_mutex_unlock(philo->etat_mutex);
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

int	ft_death_checker(t_philo *philo)
{
	struct timeval	current;
	uint64_t		curr;
	
	gettimeofday(&current, NULL);
	curr = ((current.tv_sec * (uint64_t)1000)) + (current.tv_usec / 1000);
	pthread_mutex_lock(philo->etat_mutex);
	if (curr - philo->last_meal >= philo->ms_die)
	{
		philo->state = FIRST_DEAD;
		ft_printf(philo, "has died.");
		pthread_mutex_unlock(philo->etat_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->etat_mutex);
	return (0);
}

int	ft_can_take_fork(t_philo *philo, int flag)
{
	if (flag == 1)
	{
		if (philo->fork == ON_TABLE)
			return (1);
	}
	else if (flag == 2)
	{
		if (*philo->right_fork == ON_TABLE)
			return (1);
	}
	return (0);
}

int	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_mutex);
	pthread_mutex_lock(philo->right_fork_mutex);
	while (philo->fork != IN_USE_OWN && *philo->right_fork != IN_USE)
	{
		if (ft_can_take_fork(philo, 1) == 1 && philo->fork != IN_USE_OWN)
		{
			philo->fork = IN_USE_OWN;
			ft_printf(philo, "has taken own fork (left)");
			if (ft_death_checker(philo) == 1)
			{
				pthread_mutex_unlock(philo->fork_mutex);
				pthread_mutex_unlock(philo->right_fork_mutex);	
				return (1);
			}
		}
		if (ft_can_take_fork(philo, 2) == 1 && *philo->right_fork != IN_USE)
		{
			*philo->right_fork = IN_USE;
			ft_printf(philo, "has taken right fork");
			if (ft_death_checker(philo) == 1)
			{
				pthread_mutex_unlock(philo->fork_mutex);
				pthread_mutex_unlock(philo->right_fork_mutex);		
				return (1);
			}
		}
		
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	struct timeval meal;

	pthread_mutex_lock(philo->etat_mutex);
	gettimeofday(&meal, NULL);
	philo->last_meal = ((meal.tv_sec * (uint64_t)1000)) + (meal.tv_usec / 1000);
	ft_printf(philo, "is eating");
	usleep(philo->ms_eat * 1000);
	pthread_mutex_unlock(philo->etat_mutex);
	philo->fork = ON_TABLE;
	pthread_mutex_unlock(philo->fork_mutex);
	*philo->right_fork = ON_TABLE;
	pthread_mutex_unlock(philo->right_fork_mutex);	
}

void	*ft_philosopher(void *arg)
{
	
	t_philo			*philo;
	
	philo = (t_philo *)arg;
	// Use to start every philosopher at the same time.
	pthread_mutex_lock(philo->etat_mutex);
	if (philo->philo_id % 2 == 0)
		usleep(philo->ms_eat * 1000);
	pthread_mutex_unlock(philo->etat_mutex);
	pthread_mutex_lock(philo->etat_mutex);
	philo->last_meal = philo->start_ms;
	while (philo->state != DEAD)
	{
		pthread_mutex_unlock(philo->etat_mutex);
		if (ft_take_fork(philo) == 1)
			break ;
		ft_eat(philo);
		// printf("%d\n", philo->philo_id);
		if (ft_death_checker(philo) == 1)
			break ;
		pthread_mutex_lock(philo->etat_mutex);
	}
	pthread_mutex_unlock(philo->etat_mutex);
	return (NULL);
}
		// gettimeofday(&current, NULL);
		// curr = ((current.tv_sec * (uint64_t)1000)) + (current.tv_usec / 1000);
		// printf("philo %d - %llu ms\n", philo->philo_id, curr - philo->start_ms);