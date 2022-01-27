#include "../includes/philo.h"

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
			philo->params->who_dead = philo->name;
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
