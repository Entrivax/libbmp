# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/22 10:37:14 by lpilotto          #+#    #+#              #
#    Updated: 2016/08/22 10:45:38 by lpilotto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libbmp.a
SRCFOLDER=src/
SRCFILES=create_img.c \
	  rgb.c \
	  save_to_bmp.c \
	  set_pixel.c
INCFOLDER=include/
INC=$(addprefix $(INCFOLDER),$(INCFILES))
OBJFOLDER=obj/
OBJ=$(addprefix $(OBJFOLDER),$(subst .c,.o,$(SRCFILES)))
SRC=$(addprefix $(SRCFOLDER),$(SRCFILES))
FLAGS=-Wall -Werror -Wextra

.PHONY: all clean fclean re

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

$(OBJFOLDER)%.o: $(SRCFOLDER)%.c $(INC)
	if ! [ -d "$(OBJFOLDER)" ]; then mkdir $(OBJFOLDER); fi
	gcc -I $(INCFOLDER) -c $(FLAGS) $< -o $@

clean:
	rm -rf $(OBJFOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all