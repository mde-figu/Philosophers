#include "../includes/philo.h"

static void	*dinner(void *arg)
{
	t_philo	*caio;

	caio = (t_philo *)arg;
	pthread_mutex_lock(caio->mutex_meals);
	caio->last_meal = caio->params->start_time;
	pthread_mutex_unlock(caio->mutex_meals);
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

static void	init_philosophers(t_philo *philo, t_param *param, pthread_mutex_t **forks, int total_philo)
{
	pthread_t	waiter;
	int			i;

	i = -1;
	while (++i < total_philo)
	{
		philo[i].name = i + 1;
		philo[i].forks_right = &(*forks)[i];
		philo[i].forks_left = &(*forks)[i + 1];
		philo[i].mutex_meals = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
		philo[i].params = param;
	}
	philo[i - 1].forks_left = &(*forks)[0];
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

void	init_forks(pthread_mutex_t **forks, int total_philo)
{
	int	i;

	*forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * total_philo);
	i = -1;
	while (++i < total_philo)
		pthread_mutex_init(&(*forks)[i], NULL);
}

int	main(int argc, char *argv[])
{
	t_param	param;
	t_philo	*philo;
	pthread_mutex_t *forks;
	int		i;

	i = 0;
	if ((validate_args(argc) == 1) || (entry_args_check(argc, argv) == 1))
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	init_struct(&param, philo);
	get_paramm(argv, &param, &forks);
	init_forks(&forks, param.philo_nbr);
	init_philosophers(philo, &param, &forks, param.philo_nbr);
	while (i < param.philo_nbr && forks)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(philo[i].mutex_meals);
		i++;
	}
	pthread_mutex_destroy(param.text);
	free(param.text);
	free(param.dead);
	free(forks);
	free(philo);
	return (0);
}
