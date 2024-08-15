#include "philosophers.h"

void	*malloc_handle(size_t size);
void	thread_handle(pthread_t *thread, void *(*func)(void *), void *data, t_opcode opcode);
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
	if (0 == status)
		return ;
	if (EAGAIN == status)
		error_exit(RED"No resources to create another thread.\n"RESET);
	else if (EPERM == status)
		error_exit(RED"The caller does not have appropriate permission to set the required scheduling parameters or scheduling policy.\n"RESET);
	else if (EINVAL == status && CREATE == opcode)
		error_exit(RED"The value specified by attr is invalid.\n"RESET);
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit(RED"The value specified by thread is not joinable.\n"RESET);
	else if (ESRCH == status)
		error_exit(RED"No thread could be found carresponding to that"
				"specified by the given thread ID.\n"RESET);
}

void	thread_handle(pthread_t *thread, void *(*func)(void *), void *data, t_opcode opcode)
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
	if (0 == status)
		return ;	
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode || DESTROY == opcode))
		error_exit(RED"The value specified by mutes is invalid.\n"RESET);
	else if (EINVAL == status && INIT == opcode)
		error_exit(RED"The value specified by attr is invalid.\n"RESET);
	else if (EDEADLK == status)
		error_exit(RED"Deadlock would occur if the thread blocked waiting for mutex.\n"RESET);
	else if (EPERM == status)
		error_exit(RED"The current thread does not hold a lock on mutex.\n"RESET);
	else if (ENOMEM == status)
		error_exit(RED"Insufficient memory exists to initialize the mutex.\n"RESET);
	else if (EBUSY == status)
		error_exit(RED"The mutex could not be acquired because it was already locked.\n"RESET);
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
