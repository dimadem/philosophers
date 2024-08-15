#include "philosophers.h"

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *dest);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *dest);
bool	simulation_finished(t_table *table);

/* module avoid writing LOCK / UNLOCK in every function */

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *dest)
{
	bool value;

	mutex_handle(mutex, LOCK);
	value = *dest;
	mutex_handle(mutex, UNLOCK);
	return (value);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *dest)
{
	long value;

	mutex_handle(mutex, LOCK);
	value = *dest;
	mutex_handle(mutex, UNLOCK);
	return (value);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->mutex, &table->end_simulation));
}
