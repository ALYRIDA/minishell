/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:56:30 by aareslan          #+#    #+#             */
/*   Updated: 2025/06/25 12:24:12 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if ((last->content) && (last->content[i] == '\n'))
		i++;
	clean_node->content = malloc((ft_strlen(last->content) - i) + 1);
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}

void	extract_line(t_list *stash, char **current_line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(current_line, stash);
	if (*current_line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*current_line)[j++] = stash->content[i];
				break ;
			}
			(*current_line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*current_line)[j] = '\0';
}

void	add_to_stash(t_list **stash, char *buf, int readed)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (readed + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buf[i] && i < readed)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*stash);
	last->next = new_node;
}

void	read_and_stash(int fd, t_list **stash, int *readed_ptr)
{
	char	*buf;

	while (!found_newline(*stash) && *readed_ptr != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		*readed_ptr = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && *readed_ptr == 0) || *readed_ptr == -1)
		{
			free(buf);
			return ;
		}
		buf[*readed_ptr] = '\0';
		add_to_stash(stash, buf, *readed_ptr);
		free(buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*current_line;
	int				readed;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readed = 1;
	current_line = NULL;
	read_and_stash(fd, &stash, &readed);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &current_line);
	clean_stash(&stash);
	if (current_line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(current_line);
		return (NULL);
	}
	return (current_line);
}
