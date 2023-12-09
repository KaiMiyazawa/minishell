/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_constants.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:05:32 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/27 21:46:53 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CONSTANTS_H
# define MINISHELL_CONSTANTS_H

# define DEBUG true

# define PROMPT_COLOR "\033[1;32m"
# define RESET_COLOR "\033[0m"
# define PROMPT "\033[1;32mminishell$ \033[0m"

# define SPACE_AND_TAB " \t"

# define STR_EMPTY			""
# define STR_DIR			"/"
# define STR_OLDPWD			"-"
# define STR_QUOTE			"'"
# define STR_DQUOTE			"\""
# define STR_EXPAND			"$"

# define OPTION_NONL		"-n"

# define ENV_HOME			"HOME"
# define ENV_PATH			"PATH"
# define ENV_PWD			"PWD"
# define ENV_OLDPWD			"OLDPWD"

# define MSG_SIG_QUIT		"Quit: 3"
# define MSG_SYNTAX_ERR		"syntax error"
# define MSG_EXIT			"exit"
# define MSG_NO_HOME		"HOME not set"
# define MSG_NO_OLDPWD		"OLDPWD not set"
# define MSG_ENOENT			"No such file or directory"
# define MSG_ARG_NOTNUM		"numeric argument required"
# define MSG_ARG_MANY		"too many arguments"
# define MSG_DECLARE		"declare -x "
# define MSG_INVAL_ID		"bash: %s: `%s\" : not a valid identifier\n"
# define MSG_NO_CMD			"command not found"
# define MSG_ISDIR			"Is a directory"

# define PROMPT_MINISH		"minishell $ "
# define PROMPT_HREDOC		"> "

#endif
