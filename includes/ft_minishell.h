#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
# include "libft.h"
# include <stdio.h>

# define HIST_SIZE			100

extern char **environ;

typedef struct				s_process_list
{
	char					*path;
	char					**argv;
	char					**envp;
	int						status;
	int						ampersand;
	struct s_process_list	*next;
}							t_plst;

typedef struct	s_proc_builder
{
	t_plst		*root;
	t_plst		*node;
	char		*home;
	char		*tmp;
	char		*path;
	char		*trimmed;
	char		*c;
	char		**av;
	char		**ep;
	char		**tab;
	int			*var_int;
}				t_proc;

typedef struct	s_mini_exc
{
	char			**history;
	int				**proc_tab;
	size_t			history_size;
	char			**envp;
	int				glob_pid;
	int				pid;
	int				wpid;
	int				ampersand;
	struct stat		st;
	DIR				*dr;
	struct dirent	*dent;
	int				i;
	int				j;
	int				status;
	int				flag;
}				t_mini_exc;

/*
** utils directory prototypes
*/

int		ft_free_2d(char ***tab);
char	**ft_2d_tab(size_t size);
int		ft_2dlen(char **tab);
char	**copy_remainder(t_mini_exc *glob, int size);
char	*retrieve_key(t_mini_exc *glob, char *t_key);
int		check_key(char *str);

t_plst	*new_process(t_mini_exc *glob, char *command);
void	init_proc(t_plst **procs, int amount);
void	mini_run_normal(t_mini_exc *glob, t_plst *node);
void	handle_sig_prnt(int sig);
void	handle_sig_chld(int sig);
char	*grab_value(char *str);
char	*grab_key(char *str);
void	init_mini_glob(t_mini_exc *glob);
void	start_minishell(t_mini_exc *glob);
void	free_process(t_plst **process);
int		check_if_builtin(char *str);
void	check_for_tilde(t_mini_exc *glob, char **line);
void	check_for_dollar_sign(t_mini_exc *glob, char **command);
int		expand_path(t_mini_exc *glob, char **command, int *status);
int		run_builtin(t_mini_exc *glob, t_plst *node);
void    update_history(t_mini_exc *glob, char *line);
char	**copy_environ();
char	*get_home(t_mini_exc *glob);
char	*get_pwd(t_mini_exc *glob);
char	*get_value(t_mini_exc *glob, char *key);
int		check_for_key(t_mini_exc *glob, char *key);
void	mini_update_env(t_mini_exc *glob, char *str, char *str2);
void	mini_shutdown(t_mini_exc *glob, t_plst *node);
void	mini_clear(t_mini_exc *glob, t_plst *node);
void	mini_unset_env(t_mini_exc *glob, t_plst *node);
void	print_history(t_mini_exc *glob);
void	mini_echo(t_mini_exc *glob, t_plst *node);
void	mini_set_env(t_mini_exc *glob, t_plst *node);
void	mini_print_env(t_mini_exc *glob);
void	mini_changedir(t_mini_exc *glob, t_plst *node);

#endif