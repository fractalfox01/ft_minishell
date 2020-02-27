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

extern char **environ;

typedef struct				s_process_list
{
	char					*path;
	char					**argv;
	char					**envp;
	int						ampersand;
	struct s_process_list	*next;
}							t_plst;

typedef struct	s_mini_exc
{
	char			**history;
	int				**proc_tab;
	size_t			history_size;
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

t_plst *new_process(char *command);
char	*grab_value(char *str);
char	*grab_key(char *str);
void	init_mini_glob(t_mini_exc *glob);
void	start_minishell(t_mini_exc *glob);
void	free_process(t_plst **process);
void	check_for_tilde(char **line);
void	check_for_dollar_sign(char **command);
int		expand_path(char **command);

void    update_history(t_mini_exc *glob, char *line);

// /*
// ** minishell utility functions
// */

// int		is_cd(char *str);
// int		is_setenv(char *line);
// char	*mini_get_home();

// /*
// ** enviroment lookup functions
// */

// int		check_for(char *str, char *checkfor);
// int		is_pwd(char *str);
// int		is_home(char *str);
// int		mini_is_tmpdir(char *str);
// int		mini_is_logname(char *str);
// int		mini_is_user(char *str);
// int		mini_is_oldpwd(char *str);
// int		mini_is_shell(char *str);


// /*
// ** functions for controlling shell history
// */

// void	print_history(char **history);
// void	push_history(char *command);
// void	create_history_file();
// void	destroy_history_file();

// /*
// ** Starting point of most forks
// */

// void	find_and_execute_cmd(t_mini_exc *exc);
// void    start_minishell(t_mini_exc *exc);

// void	init_mini(t_mini_exc *exc, char *cmd, int ampersand);
// void	free_mini(t_mini_exc *exc);
// /*
// ** builtins
// */

// void	mini_setenv(char *line);
// void	mini_cd(char *str);

#endif