/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:45:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/06 21:56:22 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_banner_lines_1_2(void)
{
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗");
	printf("██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝");
	printf("██║     ██║     \n");
}

static void	print_banner_lines_3_4(void)
{
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ");
	printf("██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ");
	printf("██║     ██║     \n");
}

static void	print_banner_line_5(void)
{
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗");
	printf("███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝");
	printf("╚══════╝╚══════╝\n");
}

static void	print_banner_footer(void)
{
	printf("\n");
	printf("        🐚  Sirine and Aly Rida Minishell  🐚\n");
	printf("\n");
}

void	print_welcome_banner(void)
{
	printf("\n");
	print_banner_lines_1_2();
	print_banner_lines_3_4();
	print_banner_line_5();
	print_banner_footer();
}
