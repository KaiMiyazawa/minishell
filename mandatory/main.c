/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:08:46 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/10/18 17:20:38 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

//最初に、dataに設定できる変数を設定する関数data_init
void	data_init(int ac, char **av, char **ev, t_data *data)
{
	g_state = 0;
	data->ac = ac;
	data->av = av;
	data->envp = ev;
}

int	main(int argc, char **argv, char **envp)
{
	//諸々の必要な変数を子供にもつ構造体data
	t_data	data;

	data_init(argc, argv, envp, &data);
	minishell(&data);
	exit (0);
}

//__attribute__((destructor))
//static void destructor() {
//	system("leaks -q a.out");
//}
