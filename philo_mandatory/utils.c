/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:35:18 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/27 11:33:41 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_exit(const char *msg);
long	get_time(t_time_code time_code);
void	precise_usleep(t_table *table, long usec);
bool	simulation_finished(t_table *table);

void	error_exit(const char *msg)
{
	printf(RED"%s\n"RESET, msg);
	exit(1);
}

long	get_time(t_time_code time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		error_exit(RED"Gettimeofday failed"RESET);
	if (SECONDS == time_code)
		return (time.tv_sec + time.tv_usec / 1e6);
	else if (MILLISECONDS == time_code)
		return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
	else if (MICROSECONDS == time_code)
		return (time.tv_sec * 1e6 + time.tv_usec);
	else
		error_exit(RED"Wrong input to get_time"RESET);
	return (1337);
}

void	precise_usleep(t_table *table, long usec)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSECONDS);
	while (get_time(MICROSECONDS) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECONDS) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while ((get_time(MICROSECONDS) - start) < usec)
				;
		}
		usleep(100);
	}
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->mutex, &table->end_simulation) == true);
}
