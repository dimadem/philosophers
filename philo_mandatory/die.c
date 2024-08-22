#include "philosophers.h"

void	*monitor_simulation(void *data);
static bool dead(t_philo *philo);

void	*monitor_simulation(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philosophers_number)
		{
			if (dead(&table->philos_array[i]) == true)
				break ;
		}
	}
	return (NULL);
}

static bool dead(t_philo *philo)
{
    long elapsed_time;
    long time_to_die;

    if (get_bool(&philo->mutex, &philo->full))
        return (false);
    elapsed_time = (get_time(MICROSECONDS) - philo->last_meal_time) / 1e3;
    time_to_die = philo->table->time_to_die;
    printf("last_meal_time: %ld\n", philo->last_meal_time);
    printf("elapsed_time: %ld\n", elapsed_time);
    if (elapsed_time > time_to_die)
    {
        set_bool(&philo->table->mutex, &philo->table->end_simulation, true);
        write_status(DEAD, philo, DEBUG_MODE);
        return (true);
    }
    return (false);
}