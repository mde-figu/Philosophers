#include "../includes/philo.h"

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->forks_right);
	pthread_mutex_lock(philo->forks_left);
	if (dinner_finish(philo) != 0)
		return (1);
	print_action(philo, FORK);
	print_action(philo, FORK);
	if (dinner_finish(philo) != 0)
		return (1);
	print_action(philo, EAT);
	meals(philo);
	if (dinner_finish(philo) != 0)
		return (1);
	usleep(philo->params->t_toeat * 1000);
	pthread_mutex_unlock(philo->forks_right);
	pthread_mutex_unlock(philo->forks_left);
	return (0);
}

int	sleeping(t_philo *philo)
{
	print_action(philo, SLEEP);
	usleep(philo->params->t_tosleep * 1000);
	return (0);
}

int	thinking(t_philo *philo)
{
	print_action(philo, THINK);
	usleep(1000);
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
