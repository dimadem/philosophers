NAME	=	philo

#comands
CC	=	cc
DFLAGS	=	-g
CFLAGS	=	-Wall -Wextra -Werror
RM	=	rm -f
SILENT	=	--silent

#directories
PHILO_DIR	=	./philo/
BUILD_DIR	=	./build/

#files
PHILO_SOURCES	=	$(PHILO_DIR)main.c \
					$(PHILO_DIR)philo.c \
					$(PHILO_DIR)utils.c \
					$(PHILO_DIR)time.c \
					$(PHILO_DIR)print.c \
					$(PHILO_DIR)check.c

#build
PHILO_OBJS	=	$(PHILO_SOURCES:$(PHILO_DIR)%.c=$(BUILD_DIR)%.o)

#rules
all: $(NAME)

$(NAME): $(PHILO_OBJS)
	@$(CC) $(CFLAGS) $(DFLAGS) -o $(NAME) $(PHILO_OBJS)
	@echo "philo compiled"

$(BUILD_DIR)%.o: $(PHILO_DIR)%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@
	@echo "compiled $<"

clean:
	@$(RM) $(BUILD_DIR)
	@echo "cleaned"

fclean: clean
	@$(RM) $(NAME)
	@echo "fcleaned"

re: fclean all

.PHONY: all clean fclean re
