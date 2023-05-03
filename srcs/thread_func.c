/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:13:48 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/03 10:16:09 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_eat(t_philo *philo)
{
	philo->state = EATING;
	if (ft_printf(philo, "is eating\n") == 1)
	{
		philo->fork = ON_TABLE;
		*philo->right_fork = ON_TABLE;
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
		return (1);
	}
	pthread_mutex_lock(&philo->eat_mutex);
	philo->eat_counter += 1;
	pthread_mutex_unlock(&philo->eat_mutex);
	philo->last_meal = get_time();
	ft_usleep(philo, philo->ms_eat);
	philo->fork = ON_TABLE;
	*philo->right_fork = ON_TABLE;
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(philo->right_fork_mutex);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	if (ft_printf(philo, "is sleeping\n") == 1)
		return (1);
	ft_usleep(philo, philo->ms_sleep);
	philo->state = THINKING;
	if (ft_printf(philo, "is thinking\n") == 1)
		return (1);
	return (0);
}