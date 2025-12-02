/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:36:33 by skhalil           #+#    #+#             */
/*   Updated: 2025/11/12 16:44:55 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_env_node(char *env_str)
{
	t_env	*node;
	char	*equal_sign;
	size_t	key_len;

	equal_sign = strchr(env_str, '=');
	if (!equal_sign)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	key_len = equal_sign - env_str;
	node->key = strndup(env_str, key_len);
	node->value = strdup(equal_sign + 1);
	node->next = NULL;
	return (node);
}

t_env	*init_env_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
		{
			i++;
			continue ;
		}
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}

void	print_env_list(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

// int	main(int ac, char **av, char **envp)
// {
// 	(void) ac;
// 	(void) av;
// 	t_env *env_list = init_env_list(envp);
// 	print_env_list(env_list);
// 	return (0);
// }