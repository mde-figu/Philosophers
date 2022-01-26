#ifndef	PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define FORK 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define DIE 6
# define MAX_INT 2147483647

typedef struct s_param
{
	int					philo_nbr;
	int					t_todie;
	int					t_toeat;
	int					t_tosleep;
	int					meals_nbr;
	long int			start_time;
	int					who_dead;
	pthread_mutex_t		dead;
	pthread_mutex_t		*forks;
}	t_param;

typedef struct s_philo
{
	int				name;
	long int		last_meal;
	int				meals;
	bool			satisfied;
	int				times_eat;
	int				fork_left;
	int				fork_right;
	pthread_t		thread_philo;
	t_param			*params;
}	t_philo;

/********
** DINNER
*********/
void		*dinner();
void		*end_dinner(void *phi);

/********
** PARSE
*********/
void	init_struct(t_param *param, t_philo *philo);
void	get_paramm(char *argv[], t_param *param);

int		validate_args(int argc);
int		entry_args_check(int argc, char *argv[]);

/********
** TIME
*********/
unsigned long int	time_calc(long int start_time);
unsigned long int	phil_clockins(void);
int								time_if_died(long int dead_time, long int last_meal);

/********
** UTILS
*********/

int			ft_isspace(char str);
long long    ft_atol(const char *str);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void		*ft_memset(void *s, int c, size_t n);

/********
** ROUTINE
*********/

void		only_onephilo(t_philo *one);
int			eating(t_philo *philo);
int			sleeping(t_philo *philo);
int			thinking(t_philo *philo);
int			routine(t_philo *philo);

#endif