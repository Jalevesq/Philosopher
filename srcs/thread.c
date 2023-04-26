/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:27:26 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/26 14:12:31 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// long long int	ft_get_time()
// {

// }

void	ft_printf(t_philo *philo, char *str)
{
	struct timeval current;
	u_int64_t now;

	gettimeofday(&current, NULL);
	pthread_mutex_lock(philo->fork_mutex);
	now = (current.tv_sec * (uint64_t)1000) + (current.tv_usec / 1000);
	printf("%llu ms - Philo %d %s !\n", now - philo->start_ms, philo->philo_id, str); // %llu ms - Philo %d %str
	pthread_mutex_unlock(philo->fork_mutex);
}

// void	ft_eat(t_philo *philo)
// {
	
// }

void	ft_take_fork_n_eat(t_philo *philo)
{
	struct timeval meal;
	
	pthread_mutex_lock(philo->fork_mutex);
	philo->fork = IN_USE_OWN;
	ft_printf(philo, "has taken his own fork (left)\n.");
	pthread_mutex_lock(philo->right_fork_mutex);
	*philo->right_fork = IN_USE;
	ft_printf(philo, "has taken his right fork (philo id + 1)\n.");
	ft_printf(philo, "is eating\n");
	usleep(philo->ms_eat * 1000);
	philo->eat_counter++;
	philo->last_meal = (meal.tv_sec * (uint64_t)1000) + (meal.tv_usec / 1000);
	philo->fork = ON_TABLE;
	*philo->right_fork = ON_TABLE;
	philo->state = THINKING;
	pthread_mutex_unlock(philo->fork_mutex);
	pthread_mutex_unlock(philo->right_fork_mutex);
}

void	*ft_philosopher(void *arg)
{
	t_philo			*philo;
	struct timeval	time;
	
	time_t curr;
	philo = (t_philo *)arg;
	// while (philo->flag != 1)
	// 	;
	// if (philo->philo_id % 2 == 0)
	// 	usleep(philo->ms_eat * 1000);
	while (philo->state != DEAD)
	{
		ft_take_fork_n_eat(philo);
		gettimeofday(&time, NULL);
		curr = (time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000);
		if (philo->last_meal - curr >= philo->ms_die)
		{
			philo->state = DEAD;
			ft_printf(philo, "died\n");
		}
		// gettimeofday(&time, NULL);
		// curr = (time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000);
		// if (philo->last_meal - currr >= philo.ms_die)
		// {
		// 	philo->state = DEAD;
		// 	ft_printf(philo, "died\n");
		// }
	}
	// ft_eat();
	// ft_sleep();
	// ft_think_until_can_eat();
	return (NULL);
}