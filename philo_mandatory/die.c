#include "philosophers.h"

bool dead(t_philo *philo);

bool dead(t_philo *philo)
{
    long elapsed_time;
    long time_to_die;

    if (get_bool(&philo->mutex, &philo->full))
        return (false);
    elapsed_time = get_long(&philo->mutex, &philo->last_meal_time) - get_time(MILLISECONDS);
    time_to_die = philo->table->time_to_die;
    if (elapsed_time > time_to_die)
        return (true);
    return (false);
}