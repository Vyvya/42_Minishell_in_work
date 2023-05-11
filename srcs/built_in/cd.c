#include"../../headers/minishell.h"

// Check if HOME environment variable is set
static int	is_home_set(t_ppline *ppline)
{
	t_envnode	*home;

	home = ppline->pp_list_env;
	while (home != NULL)
	{
		if (ft_strcmp(home->key, "HOME") == 0 && home->value != NULL)
			return (1);
		home = home->next;
	}
	fprintf(stderr, "cd: HOME environment variable not set\n");
	return (0);
}

// Get the directory to change to
static char	*get_directory(t_ppline *ppline)
{
	t_envnode	*home;
	char		*dir;

	home = NULL;
	dir = ppline->ppline_cmd[1];
	if (dir == NULL || ft_strcmp(dir, "~") == 0)
	{
		home = ppline->pp_list_env;
		while (home != NULL)
		{
			if (ft_strcmp(home->key, "HOME") == 0 && home->value != NULL)
				return (home->value);
			home = home->next;
		}
		return (NULL);
	}
	return (dir);
}

// Change directory to the specified directory
static int	change_directory(char *dir, t_ppline *ppline)
{
	t_envnode	*pwd;

	pwd = NULL;
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		fprintf(stderr, "cd: %s: %s\n", dir, strerror(errno));
		return (EXIT_FAILURE);
	}
	pwd = ppline->pp_list_env;
	while (pwd != NULL)
	{
		if (ft_strcmp(pwd->key, "PWD") == 0)
		{
			ft_setenv("OLDPWD", pwd->value, pwd->content, &ppline->pp_list_env);
			break ;
		}
		pwd = pwd->next;
	}
	ft_setenv("PWD", dir, pwd->content, &ppline->pp_list_env);
	return (EXIT_SUCCESS);
}

// Change directory to the previous directory
static int	change_to_previous_directory(t_ppline *ppline)
{
	t_envnode	*oldpwd;

	oldpwd = ppline->pp_list_env;
	while (oldpwd != NULL)
	{
		if (ft_strcmp(oldpwd->key, "OLDPWD") == 0 && oldpwd->value != NULL)
			break ;
		oldpwd = oldpwd->next;
	}
	if (oldpwd == NULL)
	{
		fprintf(stderr, "cd: OLDPWD not set\n");
		return (EXIT_FAILURE);
	}
	if (change_directory(oldpwd->value, ppline) == -1)
		return (-1);
	printf("%s\n", oldpwd->value);
	return (EXIT_SUCCESS);
}

// Change the current working directory
int	ft_cd(t_ppline **ppline)
{
	char	*dir;

	dir = NULL;
	if (!is_home_set(*ppline))
		return (-1);
	dir = get_directory(*ppline);
	if (dir == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		msg_error(dir, 0);
		return (EXIT_FAILURE);
	}
	if (ft_strcmp(dir, "-") == 0)
		return (change_to_previous_directory(*ppline));
	return (change_directory(dir, *ppline));
}
