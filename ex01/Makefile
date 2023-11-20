NAME = RPN
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
FILES = main \
		RPN

INCLS = RPN.hpp

SRCS = $(addsuffix .cpp, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $^

.cpp.o: $(SRCS) $(INCLS)
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re