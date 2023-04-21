#include "../../headers/minishell.h"

int execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppline	*ppline;
	// char		*cmd_path;
	// char		**mini_env_arr;

	// cmd_path = NULL;
	printf(R "EXECUTE: printing cmd_list\n" RS);
	print_cmd_list(cmd);
	// mini_env_arr = ft_mini_env_array(mini_env, ft_mini_env_size(mini_env));
	ppline = build_ppline_array(&cmd, cmd_num, mini_env);

	// echo_ctrl_off();
	// signals_default();

	printf(ORS "EXECUTE: ppline->pp_first_cmd %s\n" RS, ppline->pp_first_cmd);
	printf(ORS "EXECUTE: ppline->ppline_cmd[0] %s\n" RS, ppline->ppline_cmd[0]);
	printf(ORS "EXECUTE: ppline->ppline_cmd[1] %s\n\n" RS, ppline->ppline_cmd[1]);
	if (ppline && ppline->ppline_cmd)
	{
		if (ppline->ppline_idx == 1) //&& !ppline->ppline_cmd[1])
			ppline->pp_exit = execute_single_cmd(ppline); //, mini_env_arr, &cmd_path
		else
			ppline->pp_exit = execute_multi_cmd(ppline); //, mini_env_arr //return (execute_cmd(mini, &cmd, mini_env));
	}
	// printf(R "ppline->pp_exit: %d\n" RS, ppline->pp_exit);
	if (ppline->pp_outfile != 1)
		close(ppline->pp_outfile);
	if (ppline->pp_infile != 0)
		close(ppline->pp_infile);
	g_exit_status = ppline->pp_exit;

	// signals_at_start();
	// echo_ctrl_on();
	return (0);
}
