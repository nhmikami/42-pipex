NAME		=	libft.a
LIB			=	ar rcs
RM			=	rm -f
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

SRCS		=	ft_memmove.c \
			ft_free_arr.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_printf.c \
			ft_printf_utils.c \
			get_next_line.c

OBJS		=	$(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(LIB) $(NAME) $(OBJS)

all:		$(NAME)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re