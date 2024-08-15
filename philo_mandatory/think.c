#include "philosophers.h"

void thinking(t_philo *philo);

void thinking(t_philo *philo)
{
    write_status(THINKING, philo, DEBUG_MODE);
    // precise_usleep(philo->table->time_to_sleep, philo->table);
}
