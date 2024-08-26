#include "philosophers.h"

void free_all(t_table *table);

void free_all(t_table *table)
{
    int i;
    t_philo *curr_philo;
    t_fork *curr_fork;

    i = -1;
    while (++i < table->philosophers_number)
    {
        curr_philo = &table->philos_array[i];
        mutex_handle(&curr_philo->mutex, DESTROY);
    }
    i = -1;
    while (++i < table->philosophers_number - 1)
    {
        curr_fork = &table->forks_array[i];
        mutex_handle(&curr_fork->mutex, DESTROY);
    }
    mutex_handle(&table->mutex, DESTROY);
    mutex_handle(&table->write, DESTROY);
    free(table->philos_array);
    free(table->forks_array);
    free(table);
}