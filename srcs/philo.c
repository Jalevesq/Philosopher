/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:37:35 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/07 11:36:54 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_join_n_free(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_join(data->philo[i], NULL);
		i++;
	}
	usleep(4000);
	i = 0;
	while (i < philo->philo_nbr)
	{
		pthread_mutex_destroy(&philo[i].fork_mutex);
		pthread_mutex_destroy(&philo[i].eat_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->printf_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->start_even_mutex);
	pthread_mutex_destroy(&data->start_odd_mutex);
	free(data->philo);
	free(philo);
	free(data);
}

static void	*ft_philo_solo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("%llu ms - Philo %d %s\n",
		get_time() - philo->start_ms, philo->philo_id, "has taken a fork");
	ft_usleep(philo->ms_die);
	printf("%llu ms - Philo %d %s\n",
		get_time() - philo->start_ms, philo->philo_id, "died");
	return (NULL);
}

static void	ft_create_one_philo(t_philo *philo, t_data *data)
{
	philo->start_ms = get_time();
	pthread_create(&data->philo[0], NULL,
		ft_philo_solo, philo);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (ft_check_arg(ac, av) == 1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	philo = malloc(sizeof(t_philo) * (atoi(av[1])));
	if (!philo)
		return (1);
	ft_init_philo(philo, data, av, ac);
	if (data->philo_nbr == 1)
		ft_create_one_philo(philo, data);
	else
	{
		ft_create_philo(philo, data, data->philo_nbr);
		ft_check_state(philo, data);
	}
	ft_join_n_free(philo, data);
	return (0);
}
