#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/ft_minishell.h"
#include <sys/wait.h>

void	save_and_run(t_mini_exc *glob, char *line, t_plst **process)
{
	process[0] = new_process(glob, line);
	process[1] = process[0];
	while (process[1])
	{
		if (process[1]->ampersand == 0)
			mini_run_normal(glob, process[1]);
		if (process[1])
			process[1] = process[1]->next;
	}
	if (line && ft_strlen(line) > 0)
		update_history(glob, line);
	free_process(process);
	process[1] = NULL;
	signal(SIGINT, handle_sig_prnt);
	ft_putstr("$> ");
}

int	main(void)
{
	t_mini_exc glob;
	t_plst	**process;
	char	*line;
	char	**tab;
	int		ret;
	int		i;
	int		count = 0;
	int		flag;

	flag = 0;
	i = 0;
	ret = 0;
	// line = ft_strdup("ls -al; make re; exit"); 														// passing 03/02/20
	// line = ft_strdup("cd ~/ls_repos/vog/;ft_ls $HOME $blah $PWD $moew"); 							// passing
	// line = ft_strdup("setenv;cd ~/minishell;cd ../../tvandivi/minishell/../ls_repos/vog/..;setenv"); // passing
	// line = ft_strdup("cd $meow"); 																	// passing
	// line = ft_strdup("setenv;setenv PWD meowmeow;setenv; cd ..;setenv"); 							// passing
	tab = ft_2d_tab(15);
	
	// tab[0] = ft_strdup("cd scripts");
	// tab[1] = ft_strdup("ls -al");
	// tab[2] = ft_strdup("./dollarexpansion.sh first second thridmeow");
	// tab[3] = ft_strdup("history");
	// tab[4] = ft_strdup("cd ~");
	// tab[5] = ft_strdup("cd $pwd");
	// tab[6] = ft_strdup("echo $HOME");
	
	tab[0] = ft_strdup("meow");
	tab[1] = ft_strdup("ls -al");
	tab[2] = ft_strdup("setenv MEOW hello;setenv _BLAH_ meowmeow;setenv MEOW");
	tab[3] = ft_strdup("unsetenv _BLAH_");
	tab[4] = ft_strdup("env");
	tab[5] = ft_strdup("history");
	tab[6] = ft_strdup("echo $HOME");
	tab[7] = NULL;
	//ft_strdup("clear");
	
	tab[8] = NULL;
	// glob = NULL;
	init_mini_glob(&glob);
	process = (t_plst **)malloc(sizeof(t_plst *) * 2);
	init_proc(process, 2);

	while (tab[i])
	{
		ft_putstr("$> ");
		ret = 1;
		save_and_run(&glob, tab[i], process);
		if (ret == 0)
			break ;
		i++;
	}

	// count++;
	// ft_putstr("$> ");
	// ret = 1;
	// while (tab[i])
	// {
	// 	if (ret == 1)
	// 	{
	// 		process[0] = new_process(&glob, tab[i]);
	// 		process[1] = process[0];
	// 		while (process[1])
	// 		{
	// 			if (process[1]->ampersand == 0)
	// 				mini_run_normal(&glob, process[1]);
	// 			if (process[1])
	// 				process[1] = process[1]->next;
	// 		}
	// 		if (tab[i] && ft_strlen(tab[i]) > 0)
	// 			update_history(&glob, tab[i]);
	// 		free_process(process);
	// 		process[1] = NULL;
	// 	}
	// 	else
	// 		if (tab[i])
	// 			ft_strdel(&tab[i]);
	// 	// break ;
	// 	flag = 1;
	// 	ft_putstr("$> ");
	// 	i++;
	// }
	// // system("leaks shelltesting");
	// free(*tab);
}