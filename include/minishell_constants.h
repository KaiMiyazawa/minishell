/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_constants.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:27:51 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/08 17:19:29 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CONSTANTS_H
# define MINISHELL_CONSTANTS_H

# define CHRS_DELIM			"\t <>|"
# define CHRS_QUOTE			"$\"'"

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
# define MSG_INVAL_ID		"not a valid identifier"
# define MSG_NO_CMD			"command not found"
# define MSG_ISDIR			"Is a directory"

# define PROMPT_MINISH		"minishell $ "
# define PROMPT_HREDOC		"> "

//# define TYPE_NONE			0x00
# define TYPE_STRING		0x10
# define TYPE_IN			0x20
# define TYPE_HEREDOC		0x22
# define TYPE_OUT			0x40
# define TYPE_APPEND		0x44
# define TYPE_PIPE			0x80
# define SHIFT_TYPE			4

# define LEN_QUOTE_CLOSED	2
# define LEN_QUOTE_UNCLOSED	1

#endif
