/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:35:39 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/24 17:52:25 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define ON_TABLE 0
# define IN_USE 1
# define IN_USE_OWN 2

typedef struct s_philo
{
	int				flag;
	int				philo_id;
	int				philo_nbr;
	int				eat_counter;
	uint64_t		ms_eat;
	uint64_t		last_meal;
	uint64_t		start_ms;
	struct timeval	current;
	int				fork;
	int				*right_fork;
	pthread_t		philo;
	pthread_mutex_t	*fork_mutex;
}	t_philo;

typedef struct s_data
{
	int			philo_nbr;
	int			must_eat;
	uint64_t	time;
	uint64_t	ms_sleep;
	uint64_t	ms_eat;
	uint64_t	ms_die;
}	t_data;

#endif