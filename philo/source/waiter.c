#include "../includes/philo.h"

int who_died(t_philo *philo)
{
	int dead;

	dead = 0;
	pthread_mutex_lock(philo->params->who);
	dead = philo->params->who_dead;
	pthread_mutex_unlock(philo->params->who);
	return (dead);
}

void print_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->params->who);
	philo->params->who_dead = philo->name;
	pthread_mutex_unlock(philo->params->who);
	print_action(philo, DIE);
}

int time_die(t_philo *philo)
{
	int to_die;
	long l_meal;

	pthread_mutex_lock(philo->mutex_meals);
	to_die = philo->params->t_todie;
	l_meal = philo->last_meal;
	pthread_mutex_unlock(philo->mutex_meals);
	if (time_if_died(to_die, l_meal) == 0)
		return (0);
	return (1);
}

int verify(t_philo *philo)
{
	int i;

	i = -1;
	if (who_died(philo) != 0)
		return (1);
	if (time_die(philo) == 0 && philo->satisfied == false)
	{
		pthread_mutex_lock(philo->params->dead);
		if (who_died(philo) == 0 && philo->params->philo_nbr != 1)
			print_dead(philo);
		pthread_mutex_unlock(philo->params->dead);
		return (1);
	}
	if (philo->params->meals_nbr != 0)
	{
		while (++i < philo->params->philo_nbr)
		{
			if (philo[i].meals != philo->params->meals_nbr)
				return (0);
		}
		return (1);
	}
	return (0);
}

void *end_dinner(void *phi)
{
	t_philo *philo;

	philo = (t_philo *)phi;
	while (!verify(philo))
		continue;
	return (NULL);
}
