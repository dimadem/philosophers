/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_and_setters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:48 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/27 11:31:44 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *dest);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *dest);

/* module avoid writing LOCK / UNLOCK in every function */
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *dest)
{
	bool	value;

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

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	dest;

	mutex_handle(mutex, LOCK);
	dest = *value;
	mutex_handle(mutex, UNLOCK);
	return (dest);
}
