#ifndef	PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_param
{
	int					philo_nbr;
	int					t_todie;
	int					t_toeat;
	int					t_tosleep;
	int					meals_nbr;
	long int		start_time;
	pthread_mutex_t	*forks;
}	t_param;

typedef struct s_philo
{
	int				name;
	long int		last_meal;
	bool				death; //bool?
	bool				satisfied; //bool?
	int				times_eat;
	int				fork_left;
	int				fork_rigth;
	//pthread_mutex_t	*forks;
	pthread_t	t_philo;
	struct s_param		*params;
}	t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	*ft_memset(void *s, int c, size_t n);
void	*dinner();

#endif