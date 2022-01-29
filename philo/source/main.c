#include "../includes/philo.h"

static void	*dinner(void *arg)
{
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
	while (!routine(caio))
		continue ;
	return (NULL);
}

static void	init_philosophers(t_philo *philo, t_param *param, int total_philo)
{
	pthread_t	waiter;
	int			i;

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
		pthread_create(&philo[i].thread_philo, NULL, &dinner,
			(void *)&philo[i]);
	pthread_create(&waiter, NULL, &end_dinner, philo);
	i = -1;
	while (++i < total_philo)
		pthread_join(philo[i].thread_philo, NULL);
	pthread_join(waiter, NULL);
}

static void	print_end(t_philo	*philo)
{
	if (philo->params->who_dead != 0)
	{
		//printf("\033[0;31m%ld %i died\n\033[0m",
		//	time_calc(philo->params->start_time), philo->name);
	}
	else
		printf("Comeram %i vezes\n", philo->params->meals_nbr);
}

int	main(int argc, char *argv[])
{
	t_param	param;
	t_philo	*philo;
	int		i;

	i = 0;
	if ((validate_args(argc) == 1) || (entry_args_check(argc, argv) == 1))
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	init_struct(&param, philo);
	get_paramm(argv, &param);
	init_philosophers(philo, &param, param.philo_nbr);
	print_end(philo);
	while (i < param.philo_nbr)
	{
		pthread_mutex_destroy(&param.forks[i]);
		i++;
	}
	free(param.forks);
	free(philo);
	return (0);
}
