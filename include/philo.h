/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:35:39 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/04 14:20:45 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define ON_TABLE 0
# define IN_USE 1
# define IN_USE_OWN 2

# define EATING 1
# define THINKING 2
# define SLEEPING 3

# define DEAD 1
# define NOT_DEAD 2

# define FINISH 1
# define NOT_FINISH 2

typedef struct s_philo
{
	int				*is_dead;
	int				*finish_flag;
	int				state;
	int				philo_id;
	int				philo_nbr;
	int				eat_counter;
	int				must_eat;
	uint64_t		ms_die;
	uint64_t		ms_eat;
	uint64_t		ms_sleep;
	uint64_t		last_meal;
	uint64_t		start_ms;
	int				fork;
	int				*right_fork;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	*printf_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*start_odd_mutex;
	pthread_mutex_t	*start_even_mutex;
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	fork_mutex;
}	t_philo;

typedef struct s_data
{
	pthread_t		*philo;
	int				is_dead;
	int				finish_flag;
	int				philo_nbr;
	int				must_eat;
	uint64_t		time;
	uint64_t		ms_sleep;
	uint64_t		ms_eat;
	uint64_t		ms_die;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	start_odd_mutex;
	pthread_mutex_t	start_even_mutex;
	pthread_mutex_t	printf_mutex;
}	t_data;

int			ft_eat(t_philo *philo);
int			ft_sleep(t_philo *philo);
int			ft_isdigit(int c);
int			ft_isdead(t_philo *philo);
int			ft_isfirstdead(t_philo *philo);
int			ft_death_watcher(t_philo *philo, uint64_t now);
int			ft_printf(t_philo *philo, char *str);
int			ft_printf_meal(t_philo *philo, char *str);
uint64_t	get_time(void);
int			ft_check_arg(int ac, char **av);
void		ft_usleep(int sleep);
int			ft_atoi(const char *str);
int			ft_take_fork(t_philo *philo);
void		*ft_philosopher_even(void *arg);
void		*ft_philosopher_odd(void *arg);
void		ft_init_philo(t_philo *philo, t_data *data, char **av, int ac);
void		ft_create_philo(t_philo *philo, t_data *data, int philo_nbr);

#endif