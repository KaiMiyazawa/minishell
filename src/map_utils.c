/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:18:40 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/17 15:51:03 by kmiyazaw         ###   ########.fr       */
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
	{
		free(map[i++]);
		map[i - 1] = NULL;
	}
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
	map = (char **)ft_calloc((size + 1), sizeof(char *));
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
