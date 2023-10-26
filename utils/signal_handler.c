/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyamad <mayyamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:40:59 by mayu              #+#    #+#             */
/*   Updated: 2023/10/26 17:58:42 by mayyamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		rl_on_new_line();
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_redisplay();
	}
}

void	ft_signals(void)
{
	signal(SIGQUIT, handler);
	signal(SIGINT, handler);
}
