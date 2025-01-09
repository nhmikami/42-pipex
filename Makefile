NAME			=	pipex
BONUS_NAME		=	checker
RM				=	rm -f
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror

SRC_PATH		=	./src
BONUS_PATH		=	./src_bonus
INC_PATH		=	./include
LIB_PATH		=	./libft

SRC				=	pipex.c

BONUS_SRC		=	pipex_bonus.c

OBJ				=	$(addprefix $(SRC_PATH)/, $(SRC:.c=.o))
BONUS_OBJ		=	$(addprefix $(BONUS_PATH)/, $(BONUS_SRC:.c=.o))

INC				=	-I$(INC_PATH)

LIBFT			=	$(LIB_PATH)/libft.a

all:				$(NAME)

$(LIBFT):
					make -C $(LIB_PATH) -s

$(NAME):			$(LIBFT) $(OBJ)
						$(CC) $(CFLAGS) $(OBJ) -L$(LIB_PATH) -lft -o $(NAME)

$(SRC_PATH)%.o: $(SRC_PATH)%.c $(INC_PATH)/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

bonus:				$(BONUS_NAME)

$(BONUS_NAME):		$(LIBFT) $(BONUS_OBJ)
						$(CC) $(CFLAGS) $(BONUS_OBJ) -L$(LIB_PATH) -lft -o $(BONUS_NAME)

$(BONUS_PATH)%.o: $(BONUS_PATH)%.c $(INC_PATH)/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
					$(RM) $(OBJ) $(BONUS_OBJ)
					make clean -C $(LIB_PATH) -s

fclean:				clean
					$(RM) $(NAME) $(BONUS_NAME)
					make fclean -C $(LIB_PATH) -s

re:					fclean all

.PHONY:		all bonus clean fclean re