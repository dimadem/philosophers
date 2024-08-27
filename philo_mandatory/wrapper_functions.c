/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:35:22 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/08/15 17:42:07 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*malloc_handle(size_t size);
void	thread_handle(pthread_t *thread, void *(*func)(void *), \
			void *data, t_opcode opcode);
void	mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);

void	*malloc_handle(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_exit(RED"Malloc failed"RESET);
	return (ptr);
}

static void	thread_status(int status, t_opcode opcode)
{
	(void)opcode;
	if (0 == status)
		return ;
	if (0 != status)
		error_exit(RED"Thread error\n"RESET);
}

void	thread_handle(pthread_t *thread, void *(*func)(void *), \
			void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		thread_status(pthread_create(thread, NULL, func, data), opcode);
	else if (JOIN == opcode)
		thread_status(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		thread_status(pthread_detach(*thread), opcode);
	else
		error_exit(RED"Invalid thread opcode"RESET);
}

static void	mutex_status(int status, t_opcode opcode)
{
	(void)opcode;
	if (0 == status)
		return ;
	else if (0 != status)
		error_exit(RED"Mutex error\n"RESET);
}

void	mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		mutex_status(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		mutex_status(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		mutex_status(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		mutex_status(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit(RED"Invalid mutex opcode"RESET);
}
