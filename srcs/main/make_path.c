/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:22:46 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/24 22:09:10 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_word_len(char *s, int count)
{
	int	length;

	length = 0;
	while (s[count] && !(s[count] == ':'))
	{
		count++;
		length++;
	}
	return (length);
}

static char	*make_words(char *str, int size, int count)
{
	char	*one_word;
	int		k;

	k = 0;
	if (size == 0)
	{
		one_word = (char *)ft_calloc(sizeof(char), 2);
		if (one_word == NULL)
			return (NULL);
		one_word[k++] = '.';
	}
	else
	{
		one_word = (char *)ft_calloc(sizeof(char), (size + 1));
		if (one_word == NULL)
			return (NULL);
		while (k < size)
			one_word[k++] = str[count++];
	}
	one_word[k] = '\0';
	return (one_word);
}

static bool	do_split(char **resu_vec, const char *s, int count, int count2)
{
	while (s[count] != '\0')
	{
		resu_vec[count2] = make_words((char *)s,
				count_word_len((char *)s, count), count);
		if (!resu_vec[count2++])
		{
			while (--count2 >= 0)
				free(resu_vec[count2]);
			return (true);
		}
		count += count_word_len((char *)s, count) + 1;
	}
	if (s[count - 1] == ':')
	{
		resu_vec[count2] = (char *)ft_calloc(sizeof(char), 2);
		if (resu_vec[count2] == NULL)
		{
			while (--count2 >= 0)
				free(resu_vec[count2]);
			return (true);
		}
		resu_vec[count2][0] = '.';
		resu_vec[count2++][1] = '\0';
	}
	resu_vec[count2] = NULL;
	return (false);
}

static int	count_word(char *str)
{
	int	count;
	int	result;

	count = 0;
	result = 1;
	if (str == NULL)
		return (result);
	while (str[count] != '\0')
	{
		if (str[count] == ':')
			result++;
		count++;
	}
	return (result);
}

//getenv(PATH)をもらって、:でpathを分けて配列で返す変数
char	**make_path(const char *path_line)
{
	char	**resu_vec;

	resu_vec = (char **)ft_calloc(sizeof(char *),
			(count_word((char *)path_line) + 1));
	if (!resu_vec)
		return (NULL);
	if (path_line != NULL)
	{
		if (do_split(resu_vec, path_line, 0, 0))
		{
			free(resu_vec);
			return (NULL);
		}
	}
	else
	{
		resu_vec[0] = (char *)ft_calloc(sizeof(char), 2);
		if (resu_vec[0] == NULL)
		{
			free(resu_vec);
			return (NULL);
		}
		resu_vec[0][0] = '.';
		resu_vec[0][1] = '\0';
		resu_vec[1] = NULL;
	}
	return (resu_vec);
}
