NAME	= philo

CC		= gcc
FLAGS	= -pthread -g -Wall -Wextra -Werror -o2

HEADER	= inc/philo.h

SRC_L	= main.c utils.c inits.c simulation.c
		
SRC_DIR	= src/
SRC		= $(addprefix $(SRC_DIR), $(SRC_L))

OBJ_DIR	= obj/
OBJ_L	= $(patsubst %.c, %.o, $(SRC_L))
OBJ		= $(addprefix $(OBJ_DIR), $(OBJ_L))

CYAN	= \033[0;36m
RED		= \033[0;31m
RESET	= \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HEADER) 
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "\n$(NAME): $(CYAN)object files were created$(RESET)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(NAME): $(CYAN)$(OBJ_DIR) was created$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)$(OBJ_DIR) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all