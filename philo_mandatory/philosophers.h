#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h> // printf
# include <pthread.h> // mutex: init, destroy, lock, unlock
                      // thread: create, join, detach
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <stdbool.h> // bool
# include <limits.h> // INT_MAX
# include <errno.h> // errno

/* debug macro */
# define DEBUG_MODE 0

/* ANSI Escape Sequences for text colors */

# define RESET		"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"

/* enums */

typedef enum e_time_code
{
  SECONDS,
  MILLISECONDS,
  MICROSECONDS
}	t_time_code;

typedef enum e_opcode
{
  LOCK,
  UNLOCK,
  INIT,
  DESTROY,
  CREATE,
  JOIN,
  DETACH
}	t_opcode;

typedef enum e_p_status
{
  DEAD,
  EATING,
  SLEEPING,
  THINKING,
  TAKE_LEFT_FORK,
  TAKE_RIGHT_FORK
}	t_p_status;

/* structures */
typedef struct s_table t_table;

typedef struct s_fork
{
  pthread_mutex_t	mutex;
  int		id;
}	t_fork;

typedef struct s_philo
{
  int             id;
  long            meals_counter;
  bool            full;
  long            last_meal_time; // time massed from last meal
  t_fork          *left_fork;
  t_fork          *right_fork;
  pthread_t       thread_id;
  pthread_mutex_t mutex; // for races with the monitor
  t_table         *table;
}	t_philo;

typedef struct s_table
{
  long            philosophers_number;
  long            time_to_die;
  long            time_to_eat;
  long            time_to_sleep;
  long            meals_number; // [5] | FLAG if -1;
  long            start_simulation; // time when simulation started
  bool            end_simulation;
  bool            all_threads_ready;
  pthread_mutex_t	mutex;
  pthread_mutex_t	write;
  t_fork          *forks_array;
  t_philo         *philos_array;
}	t_table;

/* init */
void	init_table(t_table *table);

/* parsing */
void	parse_input(t_table *table, char **argv);

/* wrapper_functions */
void	*malloc_handle(size_t size);
void	mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void	thread_handle(pthread_t *thread, void *(*func)(void *), void *data, t_opcode opcode);

/* dinner */
void	dinner(t_table *table);
void	*dinner_simulation(void *data);

/* eat	*/
void	eating(t_philo *philo);

/* think	*/
void	thinking(t_philo *philo);

/* write */
void  write_status(t_p_status status, t_philo *philo, bool debug);

/* getters & setters */
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *dest);
long	get_long(pthread_mutex_t *mutex, long *dest);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);

/* utils */
void	error_exit(const char *msg);
long  get_time(t_time_code time_code);
void  precise_usleep(long usec, t_table *table);

/* monitor utils*/
void  wait_all_threads(t_table *table);

#endif
