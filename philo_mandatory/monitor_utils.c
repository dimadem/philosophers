#include "philosophers.h"

void wait_all_threads(t_table *table);

void wait_all_threads(t_table *table)
{
    while (!get_bool(&table->mutex, &table->all_threads_ready))
        ;
}