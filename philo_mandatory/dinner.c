#include "philosophers.h"

void	dinner(t_table * table);
void	*dinner_simulation(void *data);

void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	
	while(!simulation_finished(philo->table))
	{
		//1. am i full
		if (philo->full)
			break ;

		//2. eat


		//3. sleep ->write status
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);

		//4. think
		thinking(philo);

	}
	return (NULL);
}

/* simulation of the dinner */

void	dinner(t_table * table)
{
	int	i;

	i = -1;

	if (0 == table->meals_number)
		return ; // back to main & clean
	else if (1 == table->philosophers_number)
		; //TODO
	else
	{
		while(++i < table->philosophers_number)
		{
			thread_handle(&table->philos_array[i].thread_id, dinner_simulation, &table->philos_array[i], CREATE); 
		}
	}
	table->start_simulation = get_time(MILLISECONDS);

	set_bool(&table->mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philosophers_number)
		thread_handle(&table->philos_array[i].thread_id, NULL, NULL, JOIN);
}
