#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    dirs_test.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 11:36:25 by pibouill          #+#    #+#              #
#    Updated: 2024/11/19 11:36:29 by pibouill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Array of commands
commands=(
    "minishell.h"
    "minishell_tester/"
    "minishell_tester"
    "/minishell_tester"
    "/minishell_tester/"
	"./minishell_tester"
	"./minishell_tester/"
	"bla"
	"/bla"
	"bla/"
	"./bla"
	"./bla/"
    "echo blou"

)

# Loop through each command
for cmd in "${commands[@]}"; do
    echo "Running: $cmd"
    eval $cmd
    exit_code=$?

    # Check exit code
    if [ $exit_code -eq 0 ]; then
        echo "Command succeeded with exit code $exit_code"
    else
        echo "Command failed with exit code $exit_code"
    fi
    echo "----------------------------------"
done

