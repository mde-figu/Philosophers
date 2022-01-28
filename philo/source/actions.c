#include "../includes/philo.h"

static void	meals(t_philo *philo)
{
	philo->last_meal = phil_clockins();
	philo->meals++;
	if (philo->params->meals_nbr != 0)
	{
		if (philo->meals == philo->params->meals_nbr
			&& philo->satisfied == false)
			philo->satisfied = true;
	}
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->forks[philo->fork_left]);
	if (philo->params->who_dead != 0)
		return (1);
	printf("\033[0;32m%ld %i has taken the left fork\n\033[0m",
		time_calc(philo->params->start_time), philo->name);
	pthread_mutex_lock(&philo->params->forks[philo->fork_right]);
	if (philo->params->who_dead != 0)
		return (1);
	printf("\033[0;35m%ld %i has taken the right fork\n\033[0m",
		time_calc(philo->params->start_time), philo->name);
	if (philo->params->who_dead != 0)
		return (1);
	printf("\033[0;33m%ld %i is eating\n\033[0m",
		time_calc(philo->params->start_time), philo->name);
	meals(philo);
	if (philo->params->who_dead != 0)
		return (1);
	usleep(philo->params->t_toeat * 1000);
	pthread_mutex_unlock(&philo->params->forks[philo->fork_right]);
	pthread_mutex_unlock(&philo->params->forks[philo->fork_left]);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (philo->params->who_dead != 0)
		return (1);
	printf("%ld %i is sleeping\n", time_calc(philo->params->start_time),
		philo->name);
	usleep(philo->params->t_tosleep * 1000);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (philo->params->who_dead != 0)
		return (1);
	printf("\033[0;31m%ld %i is thinking\n\033[0m",
		time_calc(philo->params->start_time), philo->name);
	return (0);
}

int	routine(t_philo *philo)
{
	if (eating(philo) == 1 || philo->satisfied == true)
		return (1);
	if (sleeping(philo) == 1 || philo->satisfied == true)
		return (1);
	if (thinking(philo) == 1 || philo->satisfied == true)
		return (1);
	return (0);
}
