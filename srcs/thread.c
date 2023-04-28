/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:27:26 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/28 14:22:23 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_is_someone_dead(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->philo_nbr)
	{
		if (philo[i].state == FIRST_DEAD || philo[i].state == DEAD)
			return (1);
		i++;
	}
	return (0);
}

void	ft_printf(t_philo *philo, char *str)
{
	struct timeval curr;
	uint64_t current;

	gettimeofday(&curr, NULL);
	current = ((curr.tv_sec * (uint64_t)1000)) + (curr.tv_usec / 1000);
	pthread_mutex_lock(philo->etat_mutex);
	// if (ft_is_someone_dead(philo) == 1)
	// {
	// 	pthread_mutex_unlock(philo->etat_mutex);
	// 	return ;
	// }		
	// else
	if (ft_is_someone_dead(philo) == 0)
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
		pthread_mutex_unlock(philo->etat_mutex);
		if (ft_is_someone_dead(philo) == 0)
			ft_printf(philo, "has died.");
		return (1);
	}
	pthread_mutex_unlock(philo->etat_mutex);
	return (0);
}

int	ft_can_take_fork(t_philo *philo, int flag)
{
	if (flag == 1)
	{
		pthread_mutex_lock(philo->fork_mutex);
		if (philo->fork == ON_TABLE)
			return (1);
		pthread_mutex_unlock(philo->fork_mutex);
	}
	else if (flag == 2)
	{
		pthread_mutex_lock(philo->right_fork_mutex);
		if (*philo->right_fork == ON_TABLE)
			return (1);
		pthread_mutex_unlock(philo->right_fork_mutex);
	}
	return (0);
}

int	ft_take_fork(t_philo *philo)
{
	int left_fork_flag;
	int right_fork_flag;


	left_fork_flag = 0;
	right_fork_flag = 0;
	while (left_fork_flag == 0 && right_fork_flag == 0)
	{
		if (ft_can_take_fork(philo, 1) == 1)
		{
			if (ft_death_checker(philo) == 1)
			{
				pthread_mutex_unlock(philo->fork_mutex);
				pthread_mutex_unlock(philo->right_fork_mutex);	
				return (1);
			}
			left_fork_flag = 1;
			philo->fork = IN_USE_OWN;
			ft_printf(philo, "has taken own fork (left)");
		}
		if (ft_can_take_fork(philo, 2) == 1)
		{
			if (ft_death_checker(philo) == 1)
			{
				pthread_mutex_unlock(philo->fork_mutex);
				pthread_mutex_unlock(philo->right_fork_mutex);
				return (1);
			}
			right_fork_flag = 1;
			*philo->right_fork = IN_USE;
			ft_printf(philo, "has taken right fork");
		}
		
	}
	return (0);
}

int	ft_eat(t_philo *philo)
{
	struct timeval meal;
	int	ms_eat;

	pthread_mutex_lock(philo->etat_mutex);	
	if (philo->state == THINKING)
	{
		// if (ft_death_checker(philo) == 1)
		// {
		// 	pthread_mutex_unlock(philo->fork_mutex);
		// 	pthread_mutex_unlock(philo->right_fork_mutex);
		// 	pthread_mutex_unlock(philo->etat_mutex);
		// 	return (1);
		// }
		ms_eat = philo->ms_eat;
		philo->state = EATING;
		pthread_mutex_unlock(philo->etat_mutex);
		ft_printf(philo, "is eating");
		gettimeofday(&meal, NULL);
		pthread_mutex_lock(philo->etat_mutex);	
		philo->last_meal = ((meal.tv_sec * (uint64_t)1000)) + (meal.tv_usec / 1000);
		pthread_mutex_unlock(philo->etat_mutex);
		usleep(ms_eat * 1000);
		philo->fork = ON_TABLE;
		*philo->right_fork = ON_TABLE;
		pthread_mutex_unlock(philo->fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
		if (ft_death_checker(philo) == 1)
			return (1);
		return (0);
	}
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	int	ms_sleep;

	pthread_mutex_lock(philo->etat_mutex);
	if (philo->state == EATING)
	{
		// if (ft_death_checker(philo) == 1)
		// {
		// 	pthread_mutex_unlock(philo->etat_mutex);
		// 	return (1);
		// }
		ms_sleep = philo->ms_sleep;
		philo->state = SLEEPING;
		pthread_mutex_unlock(philo->etat_mutex);
		ft_printf(philo, "is sleeping");
		usleep(ms_sleep * 1000);
		if (ft_death_checker(philo) == 1)
			return (1);
		pthread_mutex_lock(philo->etat_mutex);
		philo->state = THINKING;
	}
	pthread_mutex_unlock(philo->etat_mutex);
	return (0);
}

void	*ft_philosopher(void *arg)
{
	
	t_philo			*philo;
	
	philo = (t_philo *)arg;
	// Use to start every philosopher at the same time.
	pthread_mutex_lock(philo->etat_mutex);
	pthread_mutex_unlock(philo->etat_mutex);
	if (philo->philo_id % 2 == 0)
		usleep(philo->ms_eat * 1000);
	pthread_mutex_lock(philo->etat_mutex);
	philo->last_meal = philo->start_ms;
	while (philo->state != DEAD)
	{
		pthread_mutex_unlock(philo->etat_mutex);
		if (ft_take_fork(philo) == 1)
			break ;
		if (ft_eat(philo) == 1)
			break ;
		if (ft_sleep(philo) == 1)
			break ;
		// printf("%d\n", philo->philo_id);

		pthread_mutex_lock(philo->etat_mutex);
	}
	pthread_mutex_unlock(philo->etat_mutex);
	return (NULL);
}
		// gettimeofday(&current, NULL);
		// curr = ((current.tv_sec * (uint64_t)1000)) + (current.tv_usec / 1000);
		// printf("philo %d - %llu ms\n", philo->philo_id, curr - philo->start_ms);