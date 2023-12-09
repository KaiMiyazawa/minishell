/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:18:40 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/09 11:35:45 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ms_map_clear(char **map, size_t size)
{
	size_t	i;

	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		free(map[i++]);
	free(map);
	map = NULL;
	return (NULL);
}

char	**ms_map_lst2map(t_list *lst)
{
	char	**map;
	t_list	*ele;
	size_t	size;
	size_t	i;

	size = ft_lstsize(lst);
	ele = lst;
	map = (char **)malloc((size + 1) * sizeof(char *));
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		map[i] = ele->content;
		ele = ele->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

size_t	ms_map_size(char **map)
{
	size_t	i;

	if (map == NULL)
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i);
}
