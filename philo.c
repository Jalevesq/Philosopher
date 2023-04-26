/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:37:35 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/24 17:42:52 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *doSomeThing(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    long time;
    struct timeval current;
    printf("Philo %d \n", philo->philo_id);
    // printf("le philo a gauche du philo %d est le philo %d\n", philo->philo_id, philo->left_philo->philo_id);
    // printf("le philo a droite du philo %d est le philo %d\n", philo->philo_id, philo->right_philo->philo_id);
    while (philo[philo->philo_nbr].flag != 1)
        ;
    // printf("Simulation start\n");
    while (1)
    {
        gettimeofday(&current, NULL);
        time = ((current.tv_sec - philo->start_sec) * 1000) + ((current.tv_usec - philo->start_usec) / 1000);
        // time -= ((philo->start_sec - philo[0].start_sec) * 1000) + ((philo->start_usec - philo[0].start_usec) / 1000);
        if (time >= philo->ms_die)
        {
            printf("%ld ms Philo %d died\n", time, philo->philo_id);
            exit(EXIT_SUCCESS);
        }
    }
    // pthread_mutex_lock(philo->philo_mutex);
    // pthread_mutex_unlock(philo->philo_mutex);

    return (NULL);
}

void    ft_init_left_right(int philo_nbr, t_philo *philo)
{
    int i;

    i = -1;
    while (++i < philo_nbr)
    {
        if (i + 1 >= philo_nbr)
            philo[i].left_philo = &philo[0];
        else
            philo[i].left_philo = &philo[i + 1];
        if (i - 1 < 0)
            philo[i].right_philo = &philo[philo_nbr - 1];
        else
            philo[i].right_philo = &philo[i - 1];
    }
}

void    ft_init_philo(int philo_nbr, t_philo *philo, char **av)
{
   int  i;
   int  j;

    i = 0;
    j = 1;
    struct timeval time;

    gettimeofday(&time, NULL);
    while (i < philo_nbr)
    {
        philo[i].start_sec = time.tv_sec;
        philo[i].start_usec = time.tv_usec;
        philo[i].flag = -1;
        philo[i].philo_nbr = atoi(av[1]);
        philo[i].ms_die = atoi(av[2]);
        philo[i].fork = ON_TABLE;
        philo[i].philo_id = j;
        philo[i].fork_mutex = malloc(sizeof(pthread_mutex_t));
        philo[i].philo = NULL;
        if (!philo[i].fork_mutex)
            return ;
        pthread_mutex_init(philo[i].fork_mutex, NULL);
        i++;
        j++;
    }
    ft_init_left_right(philo_nbr, philo);   
}

void    ft_create_philo(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->philo_nbr)
    {
        pthread_create(&philo[i].philo, NULL, doSomeThing, &philo[i]);
        usleep(20);
        i++;
    }
    philo[philo->philo_nbr - 1].flag = 1;
}

void    ft_join_and_delete_philo(t_philo *philo)
{
    int i;
    int *status;

    i = 0;
    status = NULL;
    while (i < philo->philo_nbr)
    {
        pthread_join(philo[i].philo, (void *)status);
        pthread_mutex_destroy(philo[i].fork_mutex);
        i++;
    }
    i = 0;
    while (i < philo->philo_nbr)
        free(philo[i++].fork_mutex);
    free(philo);
}

int main(int ac, char **av)
{
    (void)ac;
    if (ac > 1)
    {
        t_philo *philo;

        philo = malloc(sizeof(t_philo) * atoi(av[1]));
        if (!philo)
            return (1);
        ft_init_philo(atoi(av[1]), philo, av);
        ft_create_philo(philo);
        ft_join_and_delete_philo(philo);
    }
    return (0);
}
