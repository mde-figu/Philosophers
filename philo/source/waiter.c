#include "../includes/philo.h"

void	print_dead(t_philo *philo)
{
	philo->params->who_dead = philo->name;
	printf("\033[0;31m%ld %i died\n\033[0m",
		time_calc(philo->params->start_time), philo->name);
}

int	verify(t_philo *philo)
{
	int	i;

	i = -1;
	if (philo->params->who_dead != 0)
		return (1);
	if (time_if_died(philo->params->t_todie, philo->last_meal) == 0
		&& philo->satisfied == false)
	{
		pthread_mutex_lock(&philo->params->dead);
		if (philo->params->who_dead == 0 && philo->params->philo_nbr != 1)
			print_dead(philo);
		pthread_mutex_unlock(&philo->params->dead);
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

void	*end_dinner(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (!verify(philo))
		continue ;
	return (NULL);
}
