NAME = PmergeMe
CPP = c++
CFLAGS = -Wall -Wextra -Werror -Wc++11-extensions
CPPFLAGS = -std=c++98

SRCS =	main.cpp \
		PmergeMe.cpp

INCLS = PmergeMe.hpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(VFLAGS) -o $(NAME) $^

%.o : %.cpp $(INCLS)
	$(CPP) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
