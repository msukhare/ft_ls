
SRC_PATH = srcs/

SRC_NAME = main.c\
	   ft_userecu.c\
	   ft_sorttab.c\
	   ft_putinfol.c\
	   ft_mergesort.c\
	   ft_managefilewithflag.c\
	   ft_managefile.c\
	   ft_manageerror.c\
	   ft_manage_onefile.c\
	   ft_lstwhitflag.c\
	   ft_lst.c\
	   ft_getintab.c\
	   ft_get.c\
	   ft_flags.c\
	   ft_displayfilesflag.c\
	   ft_creatpath.c\

OBJ_PATH = obj/

CPPFLAGS = -I includes/ -I libft/include/

NAME = ft_ls

CC = gcc

MK = make -C

SRCLFT = libft/

LFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	$(MK) $(SRCLFT)
	$(CC) $(CFLAGS) -o $(NAME) $(CPPFLAGS) $(OBJ) $(LFT)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	make clean -C $(SRCLFT)
	@rm -vf $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	make fclean -C $(SRCLFT)
	rm -f $(NAME)

re: fclean all

.PHONY: al, clean, fclean, re
