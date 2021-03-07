# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-idri <mel-idri@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/08 10:36:53 by ylagtab           #+#    #+#              #
#    Updated: 2021/03/07 11:08:34 by mel-idri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#	variables																   #
# **************************************************************************** #

# name
NAME = 21sh
LIBFT = libft/libft.a
READLINE_LIB = readline/readline.a
# compilation variables
CFLAGS = -Wall -Wextra -Werror -g
CC = gcc

# objects																	   #
21sh_INC = src/twenty_one.h src/parser/parser.h src/expansion/expansion.h \
	src/typedefs.h src/errors/errors.h src/redirections/redirections.h
21sh = main.o delete_fucntions.o read_command_line.o \
	parser/parser.o parser/tokenization.o parser/tokenization_helpers.o \
	parser/construct_commands.o parser/syntax_analys.o parser/util.o \
	parser/remove_quotes.o \
	expansion/expansion.o expansion/expand_word.o expansion/tilde_expansion.o \
	expansion/env_var_expansion.o expansion/tokens_to_fileds.o \
	execution/exec_simple_command.o execution/exec_commands.o \
	execution/exec_pipe_sequence.o execution/get_executable_pathname.o \
	execution/split_pipe_sequence_commands.o \
	errors/errors.o \
	redirections/perform_redirections.o redirections/redirect_output.o \
	redirections/redirect_input.o redirections/remove_redirections_tokens.o \
	redirections/fd_aggregation.o redirections/here_document.o \
	redirections/close_output.o \
	built_in/cd.o built_in/cd_utils.o built_in/env.o built_in/env_tools.o \
	built_in/env_ops.o built_in/run_built_in.o built_in/echo.o built_in/exit.o \
	built_in/is_built_in.o

21sh_OBJS = $(addprefix $(OBJS_DIR)/, ${21sh})

# objects directory
OBJS_DIR = objs

# Colors
BLACK	= \033[30m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[93m
BLUE	= \033[34m
MAGENTA	= \033[35m
CYAN	= \033[36m
WHITE	= \033[37m
RESET	= \033[0m

# **************************************************************************** #
#	rules																	   #
# **************************************************************************** #
all: $(NAME)

$(NAME): $(21sh_OBJS) $(LIBFT) $(READLINE_LIB)
	@$(CC) -o $(NAME) $(21sh_OBJS) $(LIBFT) $(READLINE_LIB) -ltermcap
	@echo "$(GREEN)program$(RESET) $(NAME): $(GREEN)UPDATED!$(RESET)";

$(LIBFT): force
	@make -C libft/

force:

$(READLINE_LIB): force
	@make -C readline/

force:

$(21sh_OBJS): $(OBJS_DIR)/%.o : src/%.c $(21sh_INC) | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -I src/
	@echo "$(YELLOW)OBJ$(RESET) $<: $(YELLOW)UPDATED!$(RESET)";

$(OBJS_DIR):
	@if [ ! -d $(OBJS_DIR) ]; then \
		echo "$(CYAN)DIR$(RESET) $(OBJS_DIR)/: $(CYAN)CREATED!$(RESET)"; \
		mkdir $(OBJS_DIR); \
	fi;

clean:
	@make clean -C libft/
	@make clean -C readline/
	@if [ -d $(OBJS_DIR) ]; then \
		echo "$(RED)OBJ$(RESET) minishell objs: $(RED)REMOVED!$(RESET)"; \
		rm -rf $(OBJS_DIR); \
	fi;

fclean: clean
	@make fclean -C libft/
	@make fclean -C readline/
	@if [ -f $(NAME) ]; then \
		echo "$(RED)program$(RESET) $(NAME): $(RED)REMOVED!$(RESET)"; \
		rm -f $(NAME); \
	fi;

re:
	@make fclean
	@make all

.PHONY: all clean fclean re libft
