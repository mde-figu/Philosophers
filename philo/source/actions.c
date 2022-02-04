#include "../includes/philo.h"

void	meals(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_meals);
	philo->last_meal = phil_clockins();
	philo->meals++;
	if (philo->params->meals_nbr != 0)
	{
		if (philo->meals == philo->params->meals_nbr
			&& philo->satisfied == false)
			philo->satisfied = true;
	}
	pthread_mutex_unlock(philo->mutex_meals);
}

int	dinner_finish(t_philo *philo)
{
	if (who_died(philo) != 0)
	{
		pthread_mutex_unlock(philo->forks_right);
		pthread_mutex_unlock(philo->forks_left);
		return (1);
	}
	return (0);
}

void	print_action(t_philo *philo, int action)
{
	long int	time;

	pthread_mutex_lock(philo->params->text);
	time = time_calc(philo->params->start_time);
	if (who_died(philo) == 0)
	{
		if (action == FORK)
			printf("\033[0;32m%ld %i has taken a fork\n\033[0m", time,
				philo->name);
		else if (action == EAT)
			printf("\033[0;33m%ld %i is eating\n\033[0m", time, philo->name);
		else if (action == SLEEP)
			printf("%ld %i is sleeping\n", time, philo->name);
		else if (action == THINK)
			printf("\033[0;31m%ld %i is thinking\n\033[0m", time, philo->name);
		else if (action == DIE)
			printf("\033[0;31m%ld %i died\n\033[0m", time, philo->name);
	}
	else if (action == DIE)
		printf("\033[0;31m%ld %i died\n\033[0m", time, philo->name);
	pthread_mutex_unlock(philo->params->text);
}
