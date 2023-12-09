/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:19:25 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/12/01 23:05:41 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

static void	tk_trim_d_dir(t_tk *tk_list, t_tk_type type)
{
	t_tk	*tmp;

	tk_list->type = type;
	tmp = tk_list->next;
	tk_list->next = tmp->next;
	free(tmp->word);
	free(tmp);
	free(tk_list->word);
	tk_list->word = (char *)malloc(sizeof(char) * 3);
	if (type == RRDIR)
		ft_strlcpy(tk_list->word, ">>", 3);
	else
		ft_strlcpy(tk_list->word, "<<", 3);
	return ;
}

static bool	tk_is_num(char *word)
{
	int	count;

	count = 0;
	while (word[count] != '\0')
	{
		if (word[count] < '0' || word[count] > '9')
			return (false);
		count++;
	}
	return (true);
}

static void	tk_trim_tklist(t_data *data)
{
	t_tk		*tmp;

	tmp = data->tk_head;
	while (tmp->next != NULL)
	{
		if (tmp->type == RDIR && tmp->next->type == RDIR)
			tk_trim_d_dir(tmp, RRDIR);
		else if (tmp->type == LDIR && tmp->next->type == LDIR)
			tk_trim_d_dir(tmp, LLDIR);
		else if (tmp->type == STR && tk_is_num(tmp->word)
			&& (tmp->next->type == RDIR || tmp->next->type == LDIR))
			tmp->type = RINT;
		if (tmp->next != NULL)
			tmp = tmp->next;
	}
}




//list1->list2->list3
//list2->list3
void	delete_a_list(t_tk *tk_list)
{
	t_tk	*tmp;

	tmp = tk_list->next;
	if (tmp == NULL)
	{
		free(tk_list->word);
		tk_list->word = NULL;
		return ;
	}
	tk_list->type = tk_list->next->type;
	free(tk_list->word);
	tk_list->word = tk_list->next->word;
	tk_list->next = tk_list->next->next;
	tmp->word = NULL;
	tmp->next = NULL;
	free(tmp);
	return ;
}

char	*tk_strjoin_free(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}

char	*get_env_value(char *env_key, t_data *data)
{
	char	*env_value;

	(void)data;
	if (env_key[0] == '?')
		return (ft_itoa(getpid()));
	else if (ft_isdigit(env_key[0]))
		return (ft_strdup(env_key + 1));
	else
	{
		env_value = getenv(env_key);
		if (env_value == NULL)
			return (ft_strdup(""));
		else
			return (ft_strdup(env_value));
	}
}

//DOLL -> STR -> ?(maybe NULL)
//		 (DOLL)
//                                DOLL
void	expand_dollar(t_tk *tk_list, t_data *data)
{
	t_tk	*tmp;
	char		*env_value;

	tmp = tk_list->next;
	env_value = NULL;
	if (tmp->type == STR)
		env_value = get_env_value(tmp->word, data);
	else if (tmp->type == DOLL)
		env_value = ft_strdup("$");
	free(tmp->word);
	tmp->word = env_value;
	tmp->type = STR;
	delete_a_list(tk_list);
}

void	expand_quotes(t_tk *tk_list, t_data *data, bool dq_flag)
{
	t_tk	*tmp;
	t_tk_type	quate;

	quate = tk_list->type;
	tmp = tk_list->next;
	tk_list->type = STR;
	free(tk_list->word);
	tk_list->word = ft_strdup("");
	while (tmp->type != quate)
	{
		if (dq_flag && tmp->type == DOLL && (tmp->next->type == STR
				|| tmp->next->type == DOLL))
		{
			expand_dollar(tmp, data);
			continue ;
		}
		tk_list->word = tk_strjoin_free(tk_list->word, tmp->word);
		delete_a_list(tmp);
	}
	if (tmp->next != NULL)
		delete_a_list(tmp);
	else
	{
		free(tmp->word);
		tmp->word = NULL;
		free(tmp);
		tk_list->next = NULL;
	}
}

void	expander(t_data *data)
{
	t_tk	*tmp;
	t_tk	*tmp2;

	tmp = data->tk_head;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->type == SQUOTE)
			expand_quotes(tmp, data, 0);
		else if (tmp->type == DQUOTE)
			expand_quotes(tmp, data, 1);
		else if (tmp->type == DOLL && (tmp->next->type == STR
				|| tmp->next->type == DOLL))
		{
			expand_dollar(tmp, data);
			continue ;
		}
		tmp = tmp->next;
	}
	tmp = data->tk_head;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->type == STR && tmp->next->type == STR)
		{
			tmp->word = tk_strjoin_free(tmp->word, tmp->next->word);
			free(tmp->next->word);
			tmp2 = tmp->next->next;
			free(tmp->next);
			tmp->next = tmp2;
			continue ;
		}
		tmp = tmp->next;
	}
	tmp = data->tk_head;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->type == SPACE_)
		{
			delete_a_list(tmp);
			continue ;
		}
		tmp = tmp->next;
	}
}

static void confirm_token(t_tk *token)
{
	t_tk	*tmp = token;
	int		c = 0;
	const char	*type_name[] = {"STR", "RDIR", "RRDIR", "LDIR",
		"LLDIR", "SPACE_", "SQUOTE", "DQUOTE", "PIPE", "DOLL", "RINT",};
	while (tmp->next != NULL)
	{
		printf("[%d] %s %s$\n",++c,type_name[tmp->type],tmp->word);
		tmp = tmp->next;
	}
	printf("[%d] %s %s$\n",++c,type_name[tmp->type],tmp->word);
	if (tmp->next == NULL)
		printf("[%d] NULL %p$\n",++c,tmp->next);
	//t_tk_list	*tmp;

	//tmp = token;
	//while (tmp != NULL)
	//{
	//	if (tmp->word != NULL)
	//		printf("tk[%p].str = %s\n", tmp, tmp->word);
	//	else
	//		printf("tk[%p].str = NULL\n", tmp);
	//	printf("tk[%p].flag = %d\n", tmp, tmp->type);

	//	tmp = tmp->next;
	//}
}


//
void	lexer(char *line, t_data *data)
{
	t_tk_type	tmp_type;
	int			count;

	count = 0;
	data->line_size = ft_strlen(line);
	data->line = (char *)malloc(sizeof(char) * (data->line_size + 1));
	ft_strlcpy(data->line, line, data->line_size + 1);
	while (line[count])
	{
		tmp_type = tk_get_tktype(line[count]);
		tk_list_add_back(data,
			tk_list_new(tk_make_word(line + count, tmp_type), tmp_type));
		count += ft_strlen(data->tk_tail->word);
	}
	//RRDIR,LLDIR,RINTを作る
	tk_trim_tklist(data);
	expander(data);
	confirm_token(data->tk_head);
	return ;
}
