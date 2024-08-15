# colors
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"
RESET	=	"\033[0m"

NAME	=	philo

#comands
CC	=	cc
DFLAGS	=	-g
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf
SILENT	=	--silent

#directories
PHILO_DIR	=	./philo_mandatory
BUILD_DIR	=	./build/

#files
PHILO_SOURCES	=	$(PHILO_DIR)/dinner.c \
					$(PHILO_DIR)/eat.c \
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
	@$(CC) $(CFLAGS) $(DFLAGS) -o $(NAME) $(PHILO_OBJS)
	@echo $(GREEN)"philo ✅"$(RESET)

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

re: fclean all

.PHONY: all clean fclean re
