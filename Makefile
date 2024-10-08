# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 11:18:24 by dmdemirk          #+#    #+#              #
#    Updated: 2024/08/27 12:08:32 by dmdemirk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# colors
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"
RESET	=	"\033[0m"

NAME	=	philo

#comands
CC	=	cc
DFLAGS	=	-g #-g3 -gdwarf-3 -fsanitize=thread
CFLAGS	=	-Wall -Wextra -Werror -pthread #-fsanitize=thread
RM		=	rm -rf
SILENT	=	--silent

#directories
PHILO_DIR	=	./philo_mandatory
BUILD_DIR	=	./build/

#files
PHILO_SOURCES	=	$(PHILO_DIR)/die.c \
					$(PHILO_DIR)/dinner.c \
					$(PHILO_DIR)/eat.c \
					$(PHILO_DIR)/free.c \
					$(PHILO_DIR)/getters_and_setters.c \
					$(PHILO_DIR)/init.c \
					$(PHILO_DIR)/main.c \
					$(PHILO_DIR)/monitor_utils.c \
					$(PHILO_DIR)/parsing.c \
					$(PHILO_DIR)/think.c \
					$(PHILO_DIR)/utils.c \
					$(PHILO_DIR)/wrapper_functions.c \
					$(PHILO_DIR)/write_status.c \

#build
PHILO_OBJS	=	$(PHILO_SOURCES:$(PHILO_DIR)%.c=$(BUILD_DIR)%.o)

#rules
all: $(NAME)

$(NAME): $(PHILO_OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(PHILO_OBJS) $(DFLAGS)
	@echo $(GREEN)"\n✅✅✅✅✅✅✅✅✅\n✅✅✅PHILO!✅✅✅\n✅✅✅✅✅✅✅✅✅\n"$(RESET)

$(BUILD_DIR)%.o: $(PHILO_DIR)%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@
	@echo $(GREEN)"✅ $<"$(RESET)

clean:
	@$(RM) $(BUILD_DIR)
	@echo $(RED)"❗️ cleaned"$(RESET)

fclean: clean
	@$(RM) $(NAME)
	@echo $(RED)"❗️ fcleaned"$(RESET)
	@echo $(RED)"\n❗️❗️❗️❗️❗️❗️❗️❗️❗️\n❗️❗️❗️PHILO!❗️❗️❗️\n❗️❗️❗️❗️❗️❗️❗️❗️❗️\n"$(RESET)


re: fclean all

.PHONY: all clean fclean re
