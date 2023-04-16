/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:37:35 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/15 22:14:45 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// a
// // void    *doSomeThing(void *arg)
// // {
// //     t_philo *philo = (t_data *)arg;
// //     struct timeval current;
// //     struct timeval start;
    
// //     int long time;
// //     gettimeofday(&current, NULL);
// //     printf("Philo %d \n", data->philo[data->philo->philo_id].philo_id);  
// //     while (1)
// //     {
// //         gettimeofday(&start, NULL);
// //         time = ((start.tv_sec - current.tv_sec) * 1000) + ((start.tv_usec - current.tv_usec) / 1000);
// //         if (time >= data->ms_die)
// //         {
// //             printf("%ld ms Philo %d died\n", time, philo->philo_id);
// //             exit(EXIT_SUCCESS);
// //         }
// //     }
// //     // pthread_mutex_lock(philo->philo_mutex);
// //     // pthread_mutex_unlock(philo->philo_mutex);
// //     return (NULL);
// // }

// void    ft_init_philo(t_data *data)
// {
//    int  i;
//    int  j;

//     i = 0;
//     j = 1;

//     while (i < data->philo_nbr)
//     {
//         data->philo->left_fork = 0;
//         data->philo->right_fork = 0;
//         data->philo[i].philo_id = j;
//         data->philo[i].philo_mutex = malloc(sizeof(pthread_mutex_t));
//         data->philo[i].philo = NULL;
//         if (!data->philo[i].philo_mutex)
//             return ;
//         pthread_mutex_init(data->philo[i].philo_mutex, NULL);
//         i++;
//         j++;
//     }
//     i = -1;
// }

// void    ft_create_philo(t_data *data)
// {
//     int i;

//     i = 0;
//     while (i < data->philo_nbr)
//     {
//         pthread_create(&data->philo[i].philo, NULL, doSomeThing, &data);
//         usleep(50);
//         i++;
//     }
// }

// void    ft_join_and_delete_philo(t_data *data)
// {
//     int i;
//     int *status;

//     i = 0;
//     status = NULL;
//     while (i < data->philo_nbr)
//     {
//         pthread_join(data->philo[i].philo, (void *)status);
//         pthread_mutex_destroy(data->philo[i].philo_mutex);
//         i++;
//     }
//     i = 0;
//     while (i < data->philo_nbr)
//         free(data->philo[i++].philo_mutex);
//     free(data->philo);
//     free(data);
// }

// int main(int ac, char **av)
// {
//     (void)ac;
//     if (ac > 1)
//     {
//         t_data *data;

//         data = malloc(sizeof(t_data));
//         if (!data)
//             return (1);
//         data->philo_nbr = atoi(av[1]);
//         data->ms_die = atoi(av[2]);
//         // data->ms_eat = atoi(av[3]);
//         // data->ms_sleep = atoi(av[3]);
//         // data->must_eat = atoi(av[4]); // Optionnel
//         data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
//         if (!data->philo)
//             return (1);
//         ft_init_philo(data);
//         ft_create_philo(data);
//         ft_join_and_delete_philo(data);
//     }
//     return (0);
// }



void    *doSomeThing(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    struct timeval current;
    struct timeval start;
    
    int long time;
    gettimeofday(&current, NULL);
    printf("Philo %d \n", philo->philo_id);
    
    int left_philo_id = -1; // initialize with invalid value
    int right_philo_id = -1; // initialize with invalid value
    left_philo_id = (philo->philo_id + 1) % philo->philo_nbr;
    if (left_philo_id == 0)
        left_philo_id = philo->philo_nbr;
    right_philo_id = (philo->philo_id + philo->philo_nbr - 1) % philo->philo_nbr;
    if (right_philo_id == 0)
        right_philo_id = philo->philo_nbr;

    printf("the left philo of %d is %d\n", philo->philo_id, left_philo_id);
    printf("the right philo of %d is %d\n", philo->philo_id, right_philo_id);
    time = 0;
    while (1)
    {
        gettimeofday(&start, NULL);
        time = ((start.tv_sec - current.tv_sec) * 1000) + ((start.tv_usec - current.tv_usec) / 1000);
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

void    ft_init_philo(int philo_nbr, t_philo *philo, char **av)
{
   int  i;
   int  j;

    i = 0;
    j = 1;
    while (i < philo_nbr)
    {
        philo[i].philo_nbr = atoi(av[1]);
        philo[i].ms_die = atoi(av[2]);
        philo[i].philo_id = j;
        philo[i].philo_mutex = malloc(sizeof(pthread_mutex_t));
        philo[i].philo = NULL;
        if (!philo[i].philo_mutex)
            return ;
        pthread_mutex_init(philo[i].philo_mutex, NULL);
        i++;
        j++;
    }
    i = -1;
}

void    ft_create_philo(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->philo_nbr)
    {
        pthread_create(&philo[i].philo, NULL, doSomeThing, &philo[i]);
        usleep(50);
        i++;
    }
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
        pthread_mutex_destroy(philo[i].philo_mutex);
        i++;
    }
    i = 0;
    while (i < philo->philo_nbr)
        free(philo[i++].philo_mutex);
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
