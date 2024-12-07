/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:27:54 by pibouill          #+#    #+#             */
/*   Updated: 2024/12/06 14:29:54 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_string_array(char **arr)
{
	if (arr == NULL) {
		printf("NULL\n");
		return;
	}
	for (int i = 0; arr[i] != NULL; i++) {
		printf("%s ", arr[i]);
	}
	printf("\n");
}

// Function to print the contents of a t_cmd structure
void	print_command(t_cmd *cmd)
{
	if (cmd == NULL)
	{
		printf("Command is NULL\n");
		return;
	}
    printf("Command:\n");
    // Print arguments
    printf("  args: ");
    print_string_array(cmd->args);
    // Print input redirection
    printf("  input: ");
    print_string_array(cmd->input);
    // Print output redirection
    printf("  output: ");
    print_string_array(cmd->output);
    // Print append redirection
    printf("  append: ");
    print_string_array(cmd->append);
    // Print delimiter
    printf("  delimiter: ");
    print_string_array(cmd->delimiter);
}
