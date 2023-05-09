#include "../headers/minishell.h"

int	g_status = 0;


void	prompt(char	*line, t_envnode *mini_env) // struct termios *saved,  t_envnode *my_envp,
{
	int		fd;
	// struct termios saved;
	// t_token *token_head;
	// t_cmd	*cmd;
	// t_pipeline *pipeline;


	// token_head = NULL;
	// cmd = NULL;
	// pipeline = NULL;

	// if (tcgetattr(STDIN_FILENO, &saved) == -1)
    // 	perror("tcgetattr"); // handle error and return or exit as appropriate
	signal_at_beginning();
	ter_attr_handler_off();
	line = readline (GREEN "minishell_VH>> " RS);
	ter_attr_handler_on();
	// tcsetattr(STDIN_FILENO, TCSAFLUSH, saved);
	// tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	// index = getpid();
	if (!line)
	{
		printf("exit\n");
		free(line);
		exit(0);
		return ;
	}
	if (ft_strlen(line) > 0)
	{
		interp(line, mini_env);
		signal(SIGINT, signal_handler2);
		add_history(line);
		fd = open("history.log", O_CREAT | O_WRONLY | O_APPEND, 0777);
		// printf("1\n");
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		close(fd);
	}
	else
		free(line);
}

int main(int argc, char **argv, char **envp)
{
	char		*line;
	t_envnode	*mini_envp;
	struct termios	saved;

	// t_mini		*mini;
	// t_envnode *temp;

	line = NULL;
	mini_envp = NULL;
	// temp = NULL;
	if (tcgetattr(STDIN_FILENO, &saved) == -1)
    	perror("tcgetattr"); // handle error and return or exit as appropriate
	if (argc != 1 || !argv || !envp)
	{
		printf("Error arguments\n");
		return (-1);
	}
	mini_envp = duplicate_env(envp);
	if (!mini_envp)
	{
		printf("Failed to create my_environment list\n");
		return (1);
	}
	// temp = mini_envp;
	// print_mini_envp(temp);
	while (1)
	{
		// printf (YELS"STDIN_FILENO [%d]\n" RS, STDIN_FILENO);
		// printf (YELS"STDIN_FILENO [%d]\n" RS, STDOUT_FILENO);
		// handle_signal(&saved);
		// sig_handlers();
		prompt(line, mini_envp); //my_envp,
		// free(line);
	}
	// free_mini_envp(mini_envp);
	// my_free_all(t_malloc **head);
	// return (0);
	write(1, "exit\n", 6);
	free(line);
	exit (0);
}

// ft_cd(built, my_envp);
// mini_pwd2(my_envp);
// ft_echo(cmd);
// token_head = interp(line);
// args = eval_token(head);
// while (head)
// {
// 	printf("Head content main: %s\n", head->content);
// 	head = head->next;
// }
// head = head->next;
// cmd = parse(token_head);
// pipeline = split_cmds_into_pipeline(cmd);
// execute_pipeline(pipeline);
