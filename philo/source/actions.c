#include "../includes/philo.h"

static void meals(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_meals);
	philo->last_meal = phil_clockins();
	philo->meals++;
	if (philo->params->meals_nbr != 0)
	{
		if (philo->meals == philo->params->meals_nbr && philo->satisfied == false)
			philo->satisfied = true;
	}
	pthread_mutex_unlock(philo->mutex_meals);
}

int dinner_finish(t_philo *philo)
{
	if (who_died(philo) != 0)
	{
		pthread_mutex_unlock(philo->forks_right);
		pthread_mutex_unlock(philo->forks_left);
		return (1);
	}
	return (0);
}

void print_action(t_philo *philo, int action)
{
	long int time;

	pthread_mutex_lock(philo->params->text);
	time = time_calc(philo->params->start_time);
	if (who_died(philo) == 0)
	{
		if (action == FORK)
			printf("\033[0;32m%ld %i has taken a fork\n\033[0m", time, philo->name);
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

int eating(t_philo *philo)
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

int sleeping(t_philo *philo)
{
	print_action(philo, SLEEP);
	usleep(philo->params->t_tosleep * 1000);
	return (0);
}

int thinking(t_philo *philo)
{
	print_action(philo, THINK);
	usleep(1000);
	return (0);
}

int routine(t_philo *philo)
{
	if (eating(philo) == 1 || philo->satisfied == true)
		return (1);
	if (sleeping(philo) == 1 || philo->satisfied == true)
		return (1);
	if (thinking(philo) == 1 || philo->satisfied == true)
		return (1);
	return (0);
}
