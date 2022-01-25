#include "../includes/philo.h"

void	only_onephilo(t_philo *one)
{
	printf("%ld %i has taken a fork\n", time_calc(one->params->start_time), one->name);
	//printf("In %ld miliseconds %i has taken a fork\n", time_calc(one->params->start_time), one->name);
	usleep(one->params->t_todie * 1000);
	printf("%ld %i died\n", time_calc(one->params->start_time), one->name);
	//printf("In %ld miliseconds %i died\n", time_calc(one->params->start_time), one->name);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->forks[philo->fork_left]);
	if (philo->params->who_dead != 0)
		return (1);
	//printf("In %ld miliseconds %i has taken a fork\n", time_calc(philo->params->start_time), philo->name);
	printf("\033[0;32m%ld %i has taken the left fork\n\033[0m", time_calc(philo->params->start_time), philo->name);
	pthread_mutex_lock(&philo->params->forks[philo->fork_right]);
	if (philo->params->who_dead != 0)
		return (1);
	/* printf("In %ld miliseconds %i has taken a fork\n", time_calc(philo->params->start_time), philo->name);
	printf("In %ld miliseconds %i is eating\n", time_calc(philo->params->start_time), philo->name); */
	printf("\033[0;35m%ld %i has taken the right fork\n\033[0m", time_calc(philo->params->start_time), philo->name);
	if (philo->params->who_dead != 0)
		return (1);
	printf("\033[0;33m%ld %i is eating\n\033[0m", time_calc(philo->params->start_time), philo->name);
	philo->last_meal = phil_clockins();
	//philo->last_meal = time_calc(philo->params->start_time);
	//printf("%i 's last meal was in: %li", philo->name, philo->last_meal);
	philo->meals++;
	//printf("In %ld miliseconds %i meals\n", time_calc(philo->params->start_time), philo->meals);
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
	printf("%ld %i is sleeping\n", time_calc(philo->params->start_time), philo->name);
	//printf("In %ld miliseconds %i is sleeping\n", time_calc(philo->params->start_time), philo->name);
	usleep(philo->params->t_tosleep * 1000);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (philo->params->who_dead != 0)
		return (1);
	printf("\033[0;31m%ld %i is thinking\n\033[0m", time_calc(philo->params->start_time), philo->name);
	//printf("In %ld %i is thinking\n", time_calc(philo->params->start_time), philo->name);
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

int		verify(t_philo *philo)
{
	if (philo->params->who_dead != 0)
		return (1);
	if (philo->params->meals_nbr != 0)
		if (philo->meals == philo->params->meals_nbr)
		{
			philo->satisfied = true;
			return (1);
		}
	if (time_if_died(philo->params->t_todie, philo->last_meal) == 0)
		{
			pthread_mutex_lock(&philo->params->dead);
			if (philo->params->who_dead == 0 && philo->params->philo_nbr != 1)
			{
				philo->params->who_dead = philo->name;
				printf("\033[0;31m%ld %i died\n\033[0m", time_calc(philo->params->start_time), philo->name);
			}
			pthread_mutex_unlock(&philo->params->dead);
			return (1);
		}
	return (0);
}

void	*end_dinner(void *phi)
{
	t_philo *philo;

	philo = (t_philo *)phi;
	while (!verify(philo))
		continue ;
	return (NULL);
}

void	*dinner(void *arg)
{
	//pthread_t waiter;
	t_philo	*caio;

	caio = (t_philo *)arg;
	caio->last_meal = caio->params->start_time;

	if (caio->params->philo_nbr == 1)
	{
		only_onephilo(caio);
		return (NULL);
	}
	if (caio->name % 2 == 0)
		usleep(1000);
	while(!routine(caio))
		continue ;
	return (NULL);
}

static void	init_philosophers(t_philo *philo, t_param *param, int total_philo)
{
	pthread_t waiter;
	//t_philo *philo;
	//philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * total_philo);
	//philo = (t_philo *)malloc(sizeof(t_philo) * total_philo + 64);
	int i;

	i = -1;
	while (++i < total_philo)
	{
		philo[i].name = i + 1;
		philo[i].fork_left = i;
		philo[i].fork_right = (i + 1) % total_philo;
		philo[i].params = param;
	}
	i = -1;
	param->start_time = phil_clockins();
	while (++i < total_philo)
		pthread_create(&philo[i].thread_philo, NULL, &dinner, (void *)&philo[i]);
	pthread_create(&waiter, NULL, &end_dinner, philo);
	i = -1;
	while (++i < total_philo)
		pthread_join(philo[i].thread_philo, NULL);
	pthread_join(waiter, NULL);
	//exit(0);
	free(philo);
}

/* static int		init_dinner(t_philo *philo, t_param *param)
{
	init_philosophers(philo, param, param->philo_nbr);
	return (0);
} */

int	main(int argc, char *argv[])
{
	t_param param;
	t_philo *philo;
	int i;

	i = 0;
	if ((validate_args(argc) == 1) || (entry_args_check(argc, argv) == 1))
		return(1);
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	init_struct(&param, philo);
	get_paramm(argv, &param);
	init_philosophers(philo, &param, param.philo_nbr);
	/* if (init_dinner(philo, &param) != 0)
	{
		printf("rodou init_dinner, vai sair  com a comanda sem pagar, oh la!\n");
		return(1);
	} */
	while (i < param.philo_nbr)
	{
		pthread_mutex_destroy(&param.forks[i]);
		i++;
	}
	free(param.forks);
	return(0);
}
