# Philosopher

## Description

Philosopher est un projet de l'école 42 qui consiste à implémenter un programme multithreadé qui simule un groupe de philosophes qui mangent et pensent autour d'une table. Le but est de résoudre le problème classique de la synchronisation des processus pour éviter les interblocages.

Le programme est écrit en langage C et utilise les threads POSIX pour la synchronisation.

## Installation

1. Cloner le dépôt Git : git clone https://github.com/USERNAME/philosopher.git
2. Se placer dans le répertoire cloné : cd philosopher
3. Compiler le programme : make

### Utilisation

Pour exécuter le programme, utilisez la commande suivante :

./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]

Les arguments sont les suivants :

* number_of_philosophers : le nombre de philosophes (entre 2 et 200)
* time_to_die : le temps (en ms) après lequel un philosophe meurt s'il n'a pas mangé
* time_to_eat : le temps (en ms) que prend un philosophe pour manger
* time_to_sleep : le temps (en ms) que prend un philosophe pour dormir après avoir mangé
* number_of_times_each_philosopher_must_eat : le nombre de fois qu'un philosophe doit manger avant de quitter la table (optionnel)

Par exemple : ./philo 5 800 200 200 3
