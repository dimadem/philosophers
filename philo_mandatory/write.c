#include "philosophers.h"

void write_status(t_p_status status, t_philo *philo, bool debug);

static void write_status_debug(t_p_status status, t_philo *philo, long elapsed)
{
    if (TAKE_LEFT_FORK  == status)
        printf(WHITE"%6ld"RESET" %d has taken a left fork\n" "\t\t\tn"RED"[ %d ]\n", elapsed, philo->id, philo->left_fork->id);
    else if (TAKE_RIGHT_FORK == status)
        printf(WHITE"%6ld"RESET" %d has taken a right fork\n" "\t\t\tn"RED"[ %d ]\n", elapsed, philo->id, philo->right_fork->id);
    else if (EATING == status)
        printf(YELLOW"%6ld"RESET" %d is eating\n" "\t\t\tn"RED"[ %d ]\n", elapsed, philo->id, philo->right_fork->id);
    else if (SLEEPING == status)
        printf(BLUE"%6ld"RESET" %d is sleeping\n" "\t\t\tn"RED"[ %d ]\n", elapsed, philo->id, philo->right_fork->id);
    else if (THINKING == status)
        printf(YELLOW"%6ld"RESET" %d is thinking\n" "\t\t\tn"RED"[ %d ]\n", elapsed, philo->id, philo->right_fork->id);
    else if (DEAD == status)
        printf(RED"%6ld"RESET" %d died\n" "\t\t\tn"RED"[ %d ]\n", elapsed, philo->id, philo->right_fork->id);
}

void write_status(t_p_status status, t_philo *philo, bool debug)
{
    long elapsed;

    elapsed = get_time(MILLISECONDS) - philo->table->start_simulation;

    if (philo->full)
        return ;


    mutex_handle(&philo->table->write, LOCK);
    if (debug)
        write_status_debug(status, philo, elapsed);
    else
    {
        if ((TAKE_LEFT_FORK == status || TAKE_RIGHT_FORK == status)
                && !simulation_finished(philo->table))
            printf(WHITE"%6ld"RESET" %d has taken a fork\n", elapsed, philo->id);
        else if (EATING == status && !simulation_finished(philo->table))
            printf(YELLOW"%6ld"RESET" %d is eating\n", elapsed, philo->id);
        else if (SLEEPING == status && !simulation_finished(philo->table))
            printf(BLUE"%6ld"RESET" %d is sleeping\n", elapsed, philo->id);
        else if (THINKING == status && !simulation_finished(philo->table))
            printf(YELLOW"%6ld"RESET" %d is thinking\n", elapsed, philo->id);
        else if (DEAD == status)
            printf(RED"%6ld"RESET" %d died\n", elapsed, philo->id);
    }
    mutex_handle(&philo->table->write, UNLOCK);
}
