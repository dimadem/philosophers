#include "philosophers.h"

void error_exit(const char *msg);
long get_time(t_time_code time_code);
void precise_usleep(t_table *table, long usec);

void error_exit(const char *msg)
{
	printf(RED "%s\n" RESET, msg);
	exit(1);
}

/* time_code -> SECONDS MILLISECONDS MICROSECONDS */
long get_time(t_time_code time_code)
{
	struct timeval time;

	if (gettimeofday(&time, NULL))
		error_exit(RED"Gettimeofday failed"RESET);
	if (SECONDS == time_code)
		return(time.tv_sec + time.tv_usec / 1e6);
	else if (MILLISECONDS == time_code)
		return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
	else if (MICROSECONDS == time_code)
		return (time.tv_sec * 1e6 + time.tv_usec);
	else
		error_exit(RED"Wrong input to get_time"RESET);
	return (1337);
}

void precise_usleep(t_table *table, long usec)
{
	long start;
	long elapsed;
	long remaining;

	start = get_time(MICROSECONDS);
	while (get_time(MICROSECONDS) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECONDS) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else // less then 1ms
		{
			// SPINLOCK
			while ((get_time(MICROSECONDS) - start) < usec)
				;
		}
		usleep(100);
	}
}
