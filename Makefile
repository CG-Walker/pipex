CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
SRC			=	pipex.c utils.c
OBJ 		=	$(SRC:.c=.o)
NAME		=	pipex
LIBNAME		=	libft.a

all:		$(NAME)

$(NAME):	$(LIBNAME) $(OBJ)
			@$(CC) $(CFLAGS) -c $(SRC)
			@make -C ./libft
			@cp ./libft/libft.a $(LIBNAME)
			@$(CC) ${OBJ} $(LIBNAME) -o $(NAME)
			@echo "\033[32m[✓]\033[0m		[$(NAME) compiled]"

$(LIBNAME):	
			@make -C ./libft
			@cp ./libft/libft.a $(LIBNAME)

clean:
			@rm -f *.o
			@rm -f libft/*.o
			@echo "\033[32m\n[✓]\033[0m		[*.o deleted]"

fclean:		clean
			@rm -f $(NAME) a.out
			@rm -f libft/libft.a libft.a
			@rm -f outfile infile
			@rm -f libft/*.o
			@echo "\033[32m[✓]\033[0m		[$(LIBNAME) deleted]"
			@echo "\033[32m[✓]\033[0m		[$(NAME) deleted]"

re:			fclean all