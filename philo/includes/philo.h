#ifndef	PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_para
{
	int					philo_nbr;
	int					t_todie;
	int					t_toeat;
	int					t_tosleep;
	int					meals_nbr;
	long int			start_time;
}	t_para;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);

#endif