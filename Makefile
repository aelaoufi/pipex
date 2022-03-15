NAME = pipex

FILES = ft_pipex.c

HEADER = pipex.h

FLAGS = -Wall -Werror -Wextra

LIBFT = ft_libft.c

LIBFT2 = ft_libft2.c
 
OBJS =  $(LIBFT:.c=.o) $(LIBFT:.c=.o) $(FILES:.c=.o)

%.o: %.c
	cc $(FLAGS)  -c $< -o $@

$(NAME) : $(OBJS) $(HEADER)
	cc  $(FLAGS) $(LIBFT) $(LIBFT2) $(FILES) -o $(NAME)

all : $(NAME)

re : fclean all

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

.PHONY : all re clean fclean