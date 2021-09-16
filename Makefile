CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
SRC			=	pipex.c
				
OBJ 		=	$(SRC:.c=.o)
NAME		=	pipex
LIBNAME		=	libft.a

all:		$(NAME)

$(NAME):	
			@$(CC) $(CFLAGS) -c $(SRC)
			@make -C ./libft
			@cp ./libft/libft.a $(LIBNAME)
			@$(CC) ${OBJ} $(LIBNAME) -o $(NAME)
			@echo "\033[32m[✓]\033[0m		[$(NAME) compiled]"

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
			@rm -f *.o
			@rm -f libft/*.o
			@echo "\033[32m\n[✓]\033[0m		[*.o deleted]"

fclean:		clean
			@rm -f $(NAME)
			@rm -f libft/libft.a
			@rm -f outfile
			@rm -f libft.a
			@rm -f libft/*.o
			@rm -f a.out
			@echo "\033[32m[✓]\033[0m		[$(LIBNAME) deleted]"
			@echo "\033[32m[✓]\033[0m		[$(NAME) deleted]"

re:			fclean all