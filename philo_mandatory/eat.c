#include "philosophers.h"

void eating(t_philo *philo)
{
  mutex_handle(&philo->left_fork->mutex, LOCK);
  write_status(TAKE_LEFT_FORK, philo, DEBUG_MODE);
  mutex_handle(&philo->right_fork->mutex, LOCK);
  write_status(TAKE_RIGHT_FORK, philo, DEBUG_MODE);
  set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLISECONDS));
  philo->meals_counter++;
  write_status(EATING, philo, DEBUG_MODE);
  precise_usleep(philo->table->time_to_eat, philo->table);
  if (philo->table->meals_number > 0 
      && philo->meals_counter == philo->table->meals_number)
    set_bool(&philo->mutex, &philo->full, true);
  mutex_handle(&philo->left_fork->mutex, UNLOCK);
  mutex_handle(&philo->right_fork->mutex, UNLOCK);
}
