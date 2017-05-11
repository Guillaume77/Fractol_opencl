#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/29 17:16:58 by gubourge          #+#    #+#              #
#    Updated: 2017/05/03 15:11:35 by gubourge         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

LIBFT = Libft/
LIBMLX = minilibx_macos/

LIBFT_NAME = $(LIBFT)libft.a
LIBMLX_NAME = $(LIBMLX)libmlx.a
NAME = fractol

INCLUDE = -I includes/

SRCS = 	main.c \
		fractol.c \
		ft_func_ptr_init.c \
		utils.c \
		utils2.c \
		utils3.c \
		opencl.c \
		kernel_cl.c \

OBJS = $(SRCS:.c=.o)

FRAMEWORK_FLAGS = -framework OpenGL -framework AppKit -framework OpenCL
LIB_FLAGS = -lmlx
CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

$(NAME): $(OBJS)
	$(MAKE) -s -C $(LIBFT)
	$(MAKE) -s -C $(LIBMLX)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT_NAME) $(LIBMLX_NAME) $(LIB_FLAGS) $(FRAMEWORK_FLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) -s -C $(LIBFT) clean
	$(MAKE) -s -C $(LIBMLX) clean

fclean:
	$(RM) $(OBJS)
	$(RM) $(NAME)
	$(MAKE) -s -C $(LIBFT) fclean
	$(MAKE) -s -C $(LIBMLX) fclean

re: fclean all
